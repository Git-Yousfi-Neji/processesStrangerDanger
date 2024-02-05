#!/usr/bin/python3
import argparse
from ipaddress import IPv4Address, IPv6Address
from binascii import unhexlify
from struct import unpack
import tabulate


def hexint(x):
    return int(x, 16)


p = argparse.ArgumentParser()
x = p.add_mutually_exclusive_group()
x.add_argument('-t', '--tcp', action='store_const', dest='prot', const='tcp', default='tcp',
               help='Show TCP sockets (default)')
x.add_argument('-u', '--udp', action='store_const', dest='prot', const='udp',
               help='Show UDP sockets instead of TCP')
p.add_argument('-p', '--pid', type=int, required=True,
               help='Specify the process ID to filter sockets')
p.add_argument('-4', '--ipv4', action='store_const', dest='family', const='4', default='46',
               help='Show only IPv4 sockets (default is both IPv4 and IPv6)')
p.add_argument('-6', '--ipv6', action='store_const', dest='family', const='6',
               help='Show only IPv6 sockets (default is both IPv4 and IPv6)')
p.add_argument('-x', '--extra', action='store_true',
               help='Show "extra" fields which have no headers/labels')
args = p.parse_args()


# See https://www.kernel.org/doc/Documentation/networking/proc_net_tcp.txt

headers = None
output = []
fns = []
if '4' in args.family:
    fns.append(f'/proc/{args.pid}/net/{args.prot}')
if '6' in args.family:
    fns.append(f'/proc/{args.pid}/net/{args.prot}6')

for fn in fns:
    with open(fn) as inp:
        headers = next(inp).split()

        # The refcount and pointer fields are present in the data rows of both /proc/net/tcp*
        # and /proc/net/udp*, but only /proc/net/udp* has headers/labels for them.
        # https://www.kernel.org/doc/Documentation/networking/proc_net_tcp.txt
        #
        # Also, /proc/pid/net/{tcp,udp}6 have the header 'remote_address' where
        # /proc/pid/net/{tcp,udp} have 'rem_address'.
        #
        # So, an inconsistent mess. We need to fixup the header fields for sanity.
        if headers[2] == 'remote_address':
            headers[2] = 'rem_address'
        if args.prot == 'tcp' and headers == ['sl', 'local_address', 'rem_address', 'st', 'tx_queue', 'rx_queue', 'tr', 'tm->when', 'retrnsmt', 'uid', 'timeout', 'inode']:
            headers += ['ref', 'pointer']

        for line in inp:
            fields = line.split()

            lip, lp = map(unhexlify, fields[1].split(':'))
            if fn.endswith('6'):
                lip, lp = ''.join('%08x' % n for n in unpack('=4L', lip)), unpack('>H', lp)[0]
                lip = IPv6Address(':'.join(lip[4 * ii: 4 * ii + 4] for ii in range(8)))
                lbr, rbr = '[',']'
            else:
                lip, lp = IPv4Address(unpack('=L', lip)[0]), unpack('>H', lp)[0]
                lbr = rbr = ''

            rip, rp = map(unhexlify, fields[2].split(':'))
            if fn.endswith('6'):
                rip, rp = ''.join('%08x' % n for n in unpack('=4L', rip)), unpack('>H', rp)[0]
                rip = IPv6Address(':'.join(rip[4 * ii: 4 * ii + 4] for ii in range(8)))
            else:
                rip, rp = IPv4Address(unpack('=L', rip)[0]), unpack('>H', rp)[0]

            sl = int(fields[0].rstrip(':'))
            tx_queue, rx_queue = map(hexint, fields[4].split(':'))
            tr, tm_when = map(hexint, fields[5].split(':')) # TR values: https://elixir.bootlin.com/linux/latest/source/include/net/inet_connection_sock.h#L141
            st, retrnsmt = hexint(fields[3]), hexint(fields[6])
            uid, timeout, inode, refcount = map(int, fields[7:11])
            pointer = f'0x{fields[11]}' if hexint(fields[11]) != 0 else '<needs-root>'

            row = [sl, f'{lbr}{lip}{rbr}:{lp}', f'{lbr}{rip}{rbr}:{rp}', st, tx_queue, rx_queue, tr, tm_when, retrnsmt, uid, timeout, inode, refcount, pointer] + fields[12:]
            if len(row) > len(headers):
                if args.extra:
                    headers += [''] * (len(row) - len(headers))
                else:
                    row = row[:len(headers)]

            output.append(row)
if not output:  # Check if output is empty
    print("Nan")
else:
	print(tabulate.tabulate(output, headers))