
#ifndef NETWORK_ANALYZER_H
#define NETWORK_ANALYZER_H

#include "../include/networkAnalyzer.h"

CNetworkAnalyzer::CNetworkAnalyzer()
{
	
}

STcpInfo CNetworkAnalyzer::fillTcpInfo(const int pid) const
{
    return fillInfo<struct STcpInfo>(pid, "tcp");
}


SUdpInfo CNetworkAnalyzer::fillUdpInfo(const int pid) const
{
    return fillInfo<struct SUdpInfo>(pid, "udp");
}

template <typename T>
T CNetworkAnalyzer::fillInfo(const int pid, const std::string& protocol) const
{
    std::string command = "./scripts/printStructs.sh " + std::to_string(pid) + " " + protocol;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        std::cerr << "Error executing command." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::stringstream output;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        output << buffer;
    }

    pclose(pipe);

    T info;
    std::string line;
    while (std::getline(output, line))
    {
        std::istringstream iss(line);
        std::string key, value;

        if (iss >> key >> value)
        {
        	value = value.c_str();
            if (key == "sl:")
                info.sl = std::stoi(value);
            else if (key == "localAddress:")
                info.localAddress = value;
            else if (key == "rem_address:")
                info.rem_address = value;
            else if (key == "st:")
                info.st = std::stoi(value);
            else if (key == "tx_queue:")
                info.tx_queue = std::stoi(value);
            else if (key == "rx_queue:")
                info.rx_queue = std::stoi(value);
            else if (key == "tr:")
                info.tr = std::stoi(value);
            else if (key == "tm_when:")
                info.tm_when = std::stoi(value);
            else if (key == "retrnsmt:")
                info.retrnsmt = std::stoi(value);
            else if (key == "uid:")
                info.uid = std::stoi(value);
            else if (key == "timeout:")
                info.timeout = std::stoi(value);
            else if (key == "inode:")
                info.inode = std::stoi(value);
            else if (key == "ref:")
                info.ref = std::stoi(value);
            else if (key == "pointer:")
                info.pointer = value;
            else if (key == "drops:")
                info.drops = std::stoi(value);
            else if (key == "localPort:")
                info.localPort = std::stoi(value);
            else if (key == "rem_port:")
                info.remotePort = std::stoi(value);
        }
    }
    return info;
}

template <typename T>
bool CNetworkAnalyzer::isValidInfo(const T& info) const
{
    // Perform basic checks
    if (info.sl < 0 ||
        info.localAddress == "" ||
        info.localPort == 0 ||
        info.remotePort == 0)
    {
        return false;
    }
    return true;
}



void CNetworkAnalyzer::fillNetworkInfo(const int pid, SNetworkInfo* networkInfo)
{
    STcpInfo tcpInfo = fillTcpInfo(pid);
    SUdpInfo udpInfo = fillUdpInfo(pid);

    // Check if the obtained TCP and UDP information is valid before filling the structs
    if (isValidInfo(tcpInfo))
    	networkInfo->_tcp = tcpInfo;
    if (isValidInfo(udpInfo))
        networkInfo->_udp = udpInfo;
    if (!isValidInfo(tcpInfo) && !isValidInfo(udpInfo))
        std::cerr << "Error: Invalid TCP or UDP information for PID " << pid << std::endl;
}

void CNetworkAnalyzer::displayTcpInfo(const int pid, const STcpInfo& tcpInfo)
{
    if (isValidInfo(tcpInfo))
    {
    	std::cout << "Processing Tcp for PID: " << pid << std::endl;

        std::cout << "=========== TCP INFO =========" << std::endl;
        std::cout << "| Socket ID:           " << tcpInfo.sl << std::endl;
        std::cout << "| Local Address:       " << tcpInfo.localAddress << std::endl;
        std::cout << "| Local Port:          " << tcpInfo.localPort << std::endl;
        std::cout << "| Remote Address:      " << tcpInfo.rem_address << std::endl;
        std::cout << "| Remote Port:         " << tcpInfo.remotePort << std::endl;
        std::cout << "| Connection State:    " << tcpInfo.st << std::endl;
        std::cout << "| TX Queue Size:       " << tcpInfo.tx_queue << std::endl;
        std::cout << "| RX Queue Size:       " << tcpInfo.rx_queue << std::endl;
        std::cout << "| Timer Active:        " << tcpInfo.tr << std::endl;
        std::cout << "| Timer Expires:       " << tcpInfo.tm_when << std::endl;
        std::cout << "| Retransmission Count:" << tcpInfo.retrnsmt << std::endl;
        std::cout << "| User ID:             " << tcpInfo.uid << std::endl;
        std::cout << "| Timeout:             " << tcpInfo.timeout << std::endl;
        std::cout << "| Inode:               " << tcpInfo.inode << std::endl;
        std::cout << "| Reference Count:     " << tcpInfo.ref << std::endl;
        std::cout << "| Pointer:             " << tcpInfo.pointer << std::endl;
        std::cout << "| Dropped Packets:     " << tcpInfo.drops << std::endl;
        std::cout << "=============================" << std::endl;
    }
}

void CNetworkAnalyzer::displayUdpInfo(const int pid, const SUdpInfo& udpInfo)
{
    if (isValidInfo(udpInfo))
    {
    	std::cout << "Processing Udp for PID: " << pid << std::endl;

        std::cout << "=========== UDP INFO =========" << std::endl;
        std::cout << "| Socket ID:           " << udpInfo.sl << std::endl;
        std::cout << "| Local Address:       " << udpInfo.localAddress << std::endl;
        std::cout << "| Local Port:          " << udpInfo.localPort << std::endl;
        std::cout << "| Remote Address:      " << udpInfo.rem_address << std::endl;
        std::cout << "| Remote Port:         " << udpInfo.remotePort << std::endl;
        std::cout << "| Connection State:    " << udpInfo.st << std::endl;
        std::cout << "| TX Queue Size:       " << udpInfo.tx_queue << std::endl;
        std::cout << "| RX Queue Size:       " << udpInfo.rx_queue << std::endl;
        std::cout << "| Timer Active:        " << udpInfo.tr << std::endl;
        std::cout << "| Timer Expires:       " << udpInfo.tm_when << std::endl;
        std::cout << "| Retransmission Count:" << udpInfo.retrnsmt << std::endl;
        std::cout << "| User ID:             " << udpInfo.uid << std::endl;
        std::cout << "| Timeout:             " << udpInfo.timeout << std::endl;
        std::cout << "| Inode:               " << udpInfo.inode << std::endl;
        std::cout << "| Reference Count:     " << udpInfo.ref << std::endl;
        std::cout << "| Pointer:             " << udpInfo.pointer << std::endl;
        std::cout << "| Dropped Packets:     " << udpInfo.drops << std::endl;
        std::cout << "=============================" << std::endl;
    }
}

void CNetworkAnalyzer::displayNetworkInfos(const int pid, const struct SNetworkInfo *net)
{
	displayTcpInfo(pid, net->_tcp);
	displayUdpInfo(pid, net->_udp);
}


bool CNetworkAnalyzer::isLegitimateConnection(const struct SNetworkInfo* networkInfo)
{
    if (networkInfo == nullptr) {
        std::cerr << "Invalid networkInfo pointer." << std::endl;
        return false;
    }
    // Example criteria: Connection is unusual if the local port is less than 1024 and it's not in the well-known ports range.

    const bool unusualTcp = (networkInfo->_tcp.remotePort < 1024 && isWellKnownPort(networkInfo->_tcp.remotePort));
    const bool unusualUdp = (networkInfo->_udp.remotePort < 1024 && isWellKnownPort(networkInfo->_udp.remotePort));

    return unusualTcp && unusualUdp;
}

bool CNetworkAnalyzer::isWellKnownPort(unsigned int port)
{
    // Example: Define the well-known ports range (0-1023)
    return (port >= 0 && port <= 1023);
}

    
#endif // NETWORK_ANALYZER_H
