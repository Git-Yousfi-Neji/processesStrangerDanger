#!/bin/bash

# Check the number of arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <pid> <tcp|udp>"
    exit 1
fi

# Assign arguments to variables
pid="$1"
connection_type="$2"

# Check if the connection type is either "tcp" or "udp"
if [ "$connection_type" != "tcp" ] && [ "$connection_type" != "udp" ]; then
    echo "Invalid connection type. Use 'tcp' or 'udp'."
    exit 1
fi

# Run the Python script with the provided PID and capture its output
python_output=$(python3 python_scripts/parse_tcp_udp.py -p $pid --$connection_type)

# Check if the output is "Nan"
if [ "$python_output" == "Nan" ]; then
    echo "No data available for the specified process ID and protocol."
else
    # Use a flag to skip the first line
    skip_first_line=true
    
    # Iterate through each line of the Python script output
    while IFS= read -r line; do
        # Skip the first line
        if [ "$skip_first_line" = true ]; then
            skip_first_line=false
            continue
        fi

        # Check if the line contains dashes
        if [[ "$line" == -* ]]; then
            echo "===================="
        else
            # Split the line into fields
            IFS=' ' read -ra fields <<< "$line"

            # Extract local and remote ports
            local_port=${fields[1]##*:}
            rem_port=${fields[2]##*:}

            # Update localAddress and rem_address formats
            local_address="${fields[1]%%:*}"
            rem_address="${fields[2]%%:*}"

            # Check if local_address and rem_address are valid IPv4 addresses
            if [[ $local_address =~ ^[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+$ && $rem_address =~ ^[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
                # Print the updated fields in the specified format
                echo "sl: ${fields[0]}"
                echo "localAddress: $local_address"
                echo "rem_address: $rem_address"
                echo "st: ${fields[3]}"
                echo "tx_queue: ${fields[4]}"
                echo "rx_queue: ${fields[5]}"
                echo "tr: ${fields[6]}"
                echo "tm_when: ${fields[7]}"
                echo "retrnsmt: ${fields[8]}"
                echo "uid: ${fields[9]}"
                echo "timeout: ${fields[10]}"
                echo "inode: ${fields[11]}"
                echo "ref: ${fields[12]}"
                echo "pointer: ${fields[13]}"
                echo "drops: ${fields[14]}"
                echo "localPort: $local_port"
                echo "rem_port: $rem_port"
                echo "===================="
            fi
        fi
    done <<< "$python_output"
fi
