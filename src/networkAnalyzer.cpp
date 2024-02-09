
#ifndef NETWORK_ANALYZER_H
#define NETWORK_ANALYZER_H

#include "../include/networkAnalyzer.h"

CNetworkAnalyzer::CNetworkAnalyzer()
{
	
}

/**
 * @brief Retrieves TCP information for a given process ID.
 *
 * @param pid Process ID of the target process.
 * @return STcpInfo Structure containing TCP information.
 */
STcpInfo CNetworkAnalyzer::fillTcpInfo(const int pid) const
{
    return fillInfo<struct STcpInfo>(pid, "tcp");
}

/**
 * @brief Retrieves UDP information for a given process ID.
 *
 * @param pid Process ID of the target process.
 * @return SUdpInfo Structure containing UDP information.
 */
SUdpInfo CNetworkAnalyzer::fillUdpInfo(const int pid) const
{
    return fillInfo<struct SUdpInfo>(pid, "udp");
}

/**
 * @brief Template function to fill information for a given process ID and protocol.
 *
 * @tparam T Type of the structure containing information.
 * @param pid Process ID of the target process.
 * @param protocol Protocol string ("tcp" or "udp").
 * @return T Structure containing information.
 */
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

/**
 * @brief Template function to check the validity of information.
 *
 * @tparam T Type of the structure containing information.
 * @param info Structure containing information to be validated.
 * @return bool True if information is valid, false otherwise.
 */
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

/**
 * @brief Fills network information for a given process ID into a provided struct.
 *
 * @param pid Process ID of the target process.
 * @param networkInfo Pointer to the struct to hold network information.
 * @return Void
 */
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

/**
 * @brief Displays TCP information for a given process ID.
 *
 * @param pid Process ID of the target process.
 * @param tcpInfo Structure containing TCP information.
 * @return Void
 */
void CNetworkAnalyzer::displayTcpInfo(const int pid, const STcpInfo& tcpInfo)
{
    if (isValidInfo(tcpInfo))
    {
    	
#if CONFIG_WITH_LOGGING_FEATURE

        std::ofstream logFile(LOG_FILE_PATH, std::ios_base::app);

        if (!logFile.is_open())
        {
            std::cerr << "Error opening "<< LOG_FILE_PATH << std::endl;
            perror("Error details: ");
            return;
        }
        
        std::streambuf *originalCoutBuffer = std::cout.rdbuf();
        
        std::ostream console(std::cout.rdbuf());  // Create a separate console stream
        std::ostream logStream(logFile.rdbuf());   // Create a separate log stream
#else
        std::ostream& console = std::cout;
#endif

        console << "Processing Tcp for PID: " << pid << std::endl;
        console << "=========== TCP INFO =============" << std::endl;
        console << "| Socket ID:           " << tcpInfo.sl << std::endl;
        console << "| Local Address:       " << tcpInfo.localAddress << std::endl;
        console << "| Local Port:          " << tcpInfo.localPort << std::endl;
        console << "| Remote Address:      " << tcpInfo.rem_address << std::endl;
        console << "| Remote Port:         " << tcpInfo.remotePort << std::endl;
        console << "| Connection State:    " << tcpInfo.st << std::endl;
        console << "| TX Queue Size:       " << tcpInfo.tx_queue << std::endl;
        console << "| RX Queue Size:       " << tcpInfo.rx_queue << std::endl;
        console << "| Timer Active:        " << tcpInfo.tr << std::endl;
        console << "| Timer Expires:       " << tcpInfo.tm_when << std::endl;
        console << "| Retransmission Count:" << tcpInfo.retrnsmt << std::endl;
        console << "| User ID:             " << tcpInfo.uid << std::endl;
        console << "| Timeout:             " << tcpInfo.timeout << std::endl;
        console << "| Inode:               " << tcpInfo.inode << std::endl;
        console << "| Reference Count:     " << tcpInfo.ref << std::endl;
        console << "| Pointer:             " << tcpInfo.pointer << std::endl;
        console << "| Dropped Packets:     " << tcpInfo.drops << std::endl;
        console << "==================================" << std::endl;

#if CONFIG_WITH_LOGGING_FEATURE

        logStream << "Processing Tcp for PID: " << pid << std::endl;
        logStream << "=========== TCP INFO =============" << std::endl;
        logStream << "| Socket ID:           " << tcpInfo.sl << std::endl;
        logStream << "| Local Address:       " << tcpInfo.localAddress << std::endl;
        logStream << "| Local Port:          " << tcpInfo.localPort << std::endl;
        logStream << "| Remote Address:      " << tcpInfo.rem_address << std::endl;
        logStream << "| Remote Port:         " << tcpInfo.remotePort << std::endl;
        logStream << "| Connection State:    " << tcpInfo.st << std::endl;
        logStream << "| TX Queue Size:       " << tcpInfo.tx_queue << std::endl;
        logStream << "| RX Queue Size:       " << tcpInfo.rx_queue << std::endl;
        logStream << "| Timer Active:        " << tcpInfo.tr << std::endl;
        logStream << "| Timer Expires:       " << tcpInfo.tm_when << std::endl;
        logStream << "| Retransmission Count:" << tcpInfo.retrnsmt << std::endl;
        logStream << "| User ID:             " << tcpInfo.uid << std::endl;
        logStream << "| Timeout:             " << tcpInfo.timeout << std::endl;
        logStream << "| Inode:               " << tcpInfo.inode << std::endl;
        logStream << "| Reference Count:     " << tcpInfo.ref << std::endl;
        logStream << "| Pointer:             " << tcpInfo.pointer << std::endl;
        logStream << "| Dropped Packets:     " << tcpInfo.drops << std::endl;
        logStream << "==================================" << std::endl;
        
        std::cout.rdbuf(originalCoutBuffer);
        logFile.close();
        
#endif

    }
}


/**
 * @brief Displays UDP information for a given process ID.
 *
 * @param pid Process ID of the target process.
 * @param udpInfo Structure containing UDP information.
 * @return Void
 */
void CNetworkAnalyzer::displayUdpInfo(const int pid, const SUdpInfo& udpInfo)
{
    if (isValidInfo(udpInfo))
    {
    	
#if CONFIG_WITH_LOGGING_FEATURE
        
        std::ofstream logFile(LOG_FILE_PATH, std::ios_base::app);

        if (!logFile.is_open())
        {
            std::cerr << "Error opening "<< LOG_FILE_PATH << std::endl;
            perror("Error details: ");
            return;
        }
        
        std::streambuf *originalCoutBuffer = std::cout.rdbuf();
        
        std::ostream console(std::cout.rdbuf());  // Create a separate console stream
        std::ostream logStream(logFile.rdbuf());   // Create a separate log stream
        
#else
        std::ostream& console = std::cout;
#endif

        console << "Processing Udp for PID: " << pid << std::endl;
        console << "=========== UDP INFO =============" << std::endl;
        console << "| Socket ID:           " << udpInfo.sl << std::endl;
        console << "| Local Address:       " << udpInfo.localAddress << std::endl;
        console << "| Local Port:          " << udpInfo.localPort << std::endl;
        console << "| Remote Address:      " << udpInfo.rem_address << std::endl;
        console << "| Remote Port:         " << udpInfo.remotePort << std::endl;
        console << "| Connection State:    " << udpInfo.st << std::endl;
        console << "| TX Queue Size:       " << udpInfo.tx_queue << std::endl;
        console << "| RX Queue Size:       " << udpInfo.rx_queue << std::endl;
        console << "| Timer Active:        " << udpInfo.tr << std::endl;
        console << "| Timer Expires:       " << udpInfo.tm_when << std::endl;
        console << "| Retransmission Count:" << udpInfo.retrnsmt << std::endl;
        console << "| User ID:             " << udpInfo.uid << std::endl;
        console << "| Timeout:             " << udpInfo.timeout << std::endl;
        console << "| Inode:               " << udpInfo.inode << std::endl;
        console << "| Reference Count:     " << udpInfo.ref << std::endl;
        console << "| Pointer:             " << udpInfo.pointer << std::endl;
        console << "| Dropped Packets:     " << udpInfo.drops << std::endl;
        console << "==================================" << std::endl;

#if CONFIG_WITH_LOGGING_FEATURE

        logStream << "Processing Udp for PID: " << pid << std::endl;
        logStream << "=========== UDP INFO =============" << std::endl;
        logStream << "| Socket ID:           " << udpInfo.sl << std::endl;
        logStream << "| Local Address:       " << udpInfo.localAddress << std::endl;
        logStream << "| Local Port:          " << udpInfo.localPort << std::endl;
        logStream << "| Remote Address:      " << udpInfo.rem_address << std::endl;
        logStream << "| Remote Port:         " << udpInfo.remotePort << std::endl;
        logStream << "| Connection State:    " << udpInfo.st << std::endl;
        logStream << "| TX Queue Size:       " << udpInfo.tx_queue << std::endl;
        logStream << "| RX Queue Size:       " << udpInfo.rx_queue << std::endl;
        logStream << "| Timer Active:        " << udpInfo.tr << std::endl;
        logStream << "| Timer Expires:       " << udpInfo.tm_when << std::endl;
        logStream << "| Retransmission Count:" << udpInfo.retrnsmt << std::endl;
        logStream << "| User ID:             " << udpInfo.uid << std::endl;
        logStream << "| Timeout:             " << udpInfo.timeout << std::endl;
        logStream << "| Inode:               " << udpInfo.inode << std::endl;
        logStream << "| Reference Count:     " << udpInfo.ref << std::endl;
        logStream << "| Pointer:             " << udpInfo.pointer << std::endl;
        logStream << "| Dropped Packets:     " << udpInfo.drops << std::endl;
        logStream << "==================================" << std::endl;
        
        std::cout.rdbuf(originalCoutBuffer);
        logFile.close();
        
#endif

    }
}


/**
 * @brief Displays both TCP and UDP information for a given process ID.
 *
 * @param pid Process ID of the target process.
 * @param net Pointer to the struct containing network information.
 * @return Void
 */
void CNetworkAnalyzer::displayNetworkInfos(const int pid, const struct SNetworkInfo *net)
{
	displayTcpInfo(pid, net->_tcp);
	displayUdpInfo(pid, net->_udp);
}

/**
 * @brief Checks if a network connection is considered legitimate based on provided information.
 *
 * @param networkInfo Pointer to the struct containing network information.
 * @return bool True if the connection is considered legitimate, false otherwise.
 */
bool CNetworkAnalyzer::isLegitimateConnection(const struct SNetworkInfo* networkInfo)
{
    if (networkInfo == nullptr)
    {
        std::cerr << "Invalid networkInfo pointer." << std::endl;
        return false;
    }
   
    const bool unusualTcp = (networkInfo->_tcp.remotePort < 1024 && isWellKnownPort(networkInfo->_tcp.remotePort));
    const bool unusualUdp = (networkInfo->_udp.remotePort < 1024 && isWellKnownPort(networkInfo->_udp.remotePort));

    return unusualTcp && unusualUdp;
}

/**
 * @brief Checks if a given port number is considered a well-known port (<= 1023).
 *
 * @param port Port number to be checked.
 * @return bool True if the port is a well-known port, false otherwise.
 */
bool CNetworkAnalyzer::isWellKnownPort(unsigned int port)
{
    return (port <= 1023);
}

    
#endif // NETWORK_ANALYZER_H
