
#ifndef NETWORK_ANALYZER_H
#define NETWORK_ANALYZER_H

#include "../include/networkAnalyzer.h"

CNetworkAnalyzer::CNetworkAnalyzer()
{
}

STcpInfo CNetworkAnalyzer::fillTcpInfo(const int pid)
{
    STcpInfo tcpInfo;

    // Run the Python script to get TCP information
    std::string command = "python3 python_scripts/parse_tcp_udp.py --tcp --pid " + std::to_string(pid);
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        std::cerr << "Error executing command." << std::endl;
        return tcpInfo;
    }

    // Read the output of the Python script
    char buffer[128];
    std::stringstream output;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        output << buffer;
    }

    // Close the pipe
    pclose(pipe);

    // Parse the output and fill the STcpInfo struct
    std::istringstream outputStream(output.str());
    std::string line;
    std::getline(outputStream, line); // Skip the header line

    // Assuming only one line of TCP information is relevant
    std::getline(outputStream, line);

    std::istringstream lineStream(line);
    lineStream >> tcpInfo.sl >> tcpInfo.localAddress >> tcpInfo.rem_address >> tcpInfo.st >> tcpInfo.tx_queue
               >> tcpInfo.rx_queue >> tcpInfo.tr >> tcpInfo.tm_when >> tcpInfo.retrnsmt >> tcpInfo.uid
               >> tcpInfo.timeout >> tcpInfo.inode >> tcpInfo.ref >> tcpInfo.pointer >> tcpInfo.drops;

    // Extract local port from local_address
    std::size_t found = tcpInfo.localAddress.find(':');
    if (found != std::string::npos)
    {
        tcpInfo.localPort = tcpInfo.localAddress.substr(found + 1);
    }

    // Extract remote port from rem_address
    found = tcpInfo.rem_address.find(':');
    if (found != std::string::npos)
    {
        tcpInfo.remotePort = tcpInfo.rem_address.substr(found + 1);
    }

    // Convert port numbers from hexadecimal to decimal
try {
    std::size_t localPortPos, remotePortPos;
    unsigned long localPort = std::stoul(tcpInfo.localPort, &localPortPos, 16);
    unsigned long remotePort = std::stoul(tcpInfo.remotePort, &remotePortPos, 16);

    if (localPortPos == tcpInfo.localPort.length() && remotePortPos == tcpInfo.remotePort.length())
    {
        // Conversion successful
        tcpInfo.localPort = std::to_string(localPort);
        tcpInfo.remotePort = std::to_string(remotePort);
    } else
    {
        // Handle conversion failure
        std::cerr << "Error converting port numbers from hexadecimal to decimal." << std::endl;
    }
} catch (const std::invalid_argument& e)
{
    // Handle invalid argument exception
    std::cerr << "Error converting port numbers: " << e.what() << std::endl;
} catch (const std::out_of_range& e)
{
    // Handle out-of-range exception
    std::cerr << "Error converting port numbers: " << e.what() << std::endl;
}


    return tcpInfo;
}

SUdpInfo CNetworkAnalyzer::fillUdpInfo(const int pid)
{
    SUdpInfo udpInfo;

    // Run the Python script to get UDP information
    std::string command = "python3 python_scripts/parse_tcp_udp.py --udp --pid " + std::to_string(pid);
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        std::cerr << "Error executing command." << std::endl;
        return udpInfo;
    }

    // Read the output of the Python script
    char buffer[128];
    std::stringstream output;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        output << buffer;
    }

    // Close the pipe
    pclose(pipe);

    // Parse the output and fill the SUdpInfo struct
    std::istringstream outputStream(output.str());
    std::string line;
    std::getline(outputStream, line); // Skip the header line

    // Assuming only one line of UDP information is relevant
    std::getline(outputStream, line);

    std::istringstream lineStream(line);
    lineStream >> udpInfo.sl >> udpInfo.localAddress >> udpInfo.rem_address >> udpInfo.st >> udpInfo.tx_queue
               >> udpInfo.rx_queue >> udpInfo.tr >> udpInfo.tm_when >> udpInfo.retrnsmt >> udpInfo.uid
               >> udpInfo.timeout >> udpInfo.inode >> udpInfo.ref >> udpInfo.pointer >> udpInfo.drops;

    // Extract local port from local_address
    std::size_t found = udpInfo.localAddress.find(':');
    if (found != std::string::npos)
    {
        udpInfo.localPort = udpInfo.localAddress.substr(found + 1);
    }

    // Extract remote port from rem_address
    found = udpInfo.rem_address.find(':');
    if (found != std::string::npos)
    {
        udpInfo.remotePort = udpInfo.rem_address.substr(found + 1);
    }

    // Convert port numbers from hexadecimal to decimal
try {
    std::size_t localPortPos, remotePortPos;
    unsigned long localPort = std::stoul(udpInfo.localPort, &localPortPos, 16);
    unsigned long remotePort = std::stoul(udpInfo.remotePort, &remotePortPos, 16);

    if (localPortPos == udpInfo.localPort.length() && remotePortPos == udpInfo.remotePort.length())
    {
        // Conversion successful
        udpInfo.localPort = std::to_string(localPort);
        udpInfo.remotePort = std::to_string(remotePort);
    }
    else
    {
        // Handle conversion failure
        std::cerr << "Error converting port numbers from hexadecimal to decimal." << std::endl;
    }
} catch (const std::invalid_argument& e) {
    // Handle invalid argument exception
    std::cerr << "Error converting port numbers: " << e.what() << std::endl;
} catch (const std::out_of_range& e) {
    // Handle out-of-range exception
    std::cerr << "Error converting port numbers: " << e.what() << std::endl;
}


    return udpInfo;
}
// Function to fill Unix information
SUnixInfo CNetworkAnalyzer::fillUnixInfo(const int pid)
{
    SUnixInfo unixInfo;

    std::string filePath = "/proc/" + std::to_string(pid) + "/net/unix";

    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return unixInfo;  // Return an empty SUnixInfo on error
    }

    // Skip the header line
    std::string header;
    std::getline(file, header);

    // Parse the content
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string num, refCount, protocol, flags, type, st, inode, path;

        iss >> num >> refCount >> protocol >> flags >> type >> st >> inode >> path;

        if (!path.empty())
        {
            unixInfo.socketType = type;
            unixInfo.socketPath = path;
            // Add other members as needed.
            break;  // Assuming only one entry is needed for now
        }
    }

    // Close the file
    file.close();

    return unixInfo;
}


// Implementation to fill the SNetworkInfo structure.
void CNetworkAnalyzer::fillNetworkInfo(const int pid, SNetworkInfo *networkInfo)
{
    networkInfo->_tcp = fillTcpInfo(pid);
    networkInfo->_udp = fillUdpInfo(pid);
    networkInfo->_unix = fillUnixInfo(pid);
}

void CNetworkAnalyzer::displayNetworkInfos(const struct SNetworkInfo *net)
{
    std::cout << "=========== NETWORK INFO =========" << std::endl;
    
    std::cout << "TCP:" << std::endl;
    std::cout << "| Local Address:\t" << net->_tcp.localAddress << std::endl;
    std::cout << "| Local Port:\t\t" << net->_tcp.localPort << std::endl;
    std::cout << "| Remote Address:\t" << net->_tcp.rem_address << std::endl;
    std::cout << "| Remote Port:\t\t" << net->_tcp.remotePort << std::endl;
    std::cout << "| State:\t\t" << net->_tcp.st << std::endl;

    std::cout << "UDP:" << std::endl;
    std::cout << "| Local Address:\t" << net->_udp.localAddress << std::endl;
    std::cout << "| Local Port:\t\t" << net->_udp.localPort << std::endl;

    std::cout << "Unix:" << std::endl;
    std::cout << "| Socket Type:\t\t" << net->_unix.socketType << std::endl;
    std::cout << "| Socket Path:\t\t" << net->_unix.socketPath << std::endl;

    std::cout << "===================================" << std::endl;
}


bool CNetworkAnalyzer::isUnusualNetworkConnection(const struct SNetworkInfo *networkInfo)
{
	return false;
}
    
#endif // NETWORK_ANALYZER_H
