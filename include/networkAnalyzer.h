
#ifndef NETWORK_ANALYSER_H
#define NETWORK_ANALYSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <array>
#include <iostream>
#include <memory>
#include <vector>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>


#include "processManager.h"
#include "../config/config.h"


struct STcpInfo
{
    int sl;
    std::string localAddress;
    std::string rem_address;
    int st;
    int tx_queue;
    int rx_queue;
    int tr;
    int tm_when;
    int retrnsmt;
    int uid;
    int timeout;
    int inode;
    int ref;
    std::string pointer;
    int drops;
    unsigned int localPort;
    unsigned int remotePort;
};

// Structure to hold UDP connection information.
struct SUdpInfo
{
    int sl;
    std::string localAddress;
    std::string rem_address;
    int st;
    int tx_queue;
    int rx_queue;
    int tr;
    int tm_when;
    int retrnsmt;
    int uid;
    int timeout;
    int inode;
    int ref;
    std::string pointer;
    int drops;
    unsigned int localPort;
    unsigned int remotePort;
};

// Structure to hold Unix domain socket information.
struct SUnixInfo
{
    std::string socketType;  // e.g., "DGRAM", "STREAM"
    std::string socketPath;
};

// Structure to hold overall network information.
struct SNetworkInfo
{
    struct STcpInfo _tcp;
    struct SUdpInfo _udp;
    struct SUnixInfo _unix;
};


class CNetworkAnalyzer
{
	public:
		CNetworkAnalyzer();
		void fillNetworkInfo(const int pid, struct SNetworkInfo *networkInfo);
		bool isLegitimateConnection(const struct SNetworkInfo *networkInfo);
		
		void displayNetworkInfos(int pid,const struct SNetworkInfo *net);
	private:
		template <typename T>
		T fillInfo(const int pid, const std::string& protocol) const;
		template <typename T>
		bool isValidInfo(const T& info) const;
		
		void displayTcpInfo(const int pid, const STcpInfo& tcpInfo);
		void displayUdpInfo(const int pid, const SUdpInfo& udpInfo);
		
		STcpInfo fillTcpInfo(const int pid) const;
		SUdpInfo fillUdpInfo(const int pid) const;
		//SUnixInfo fillUnixInfo(const int pid);
		bool isWellKnownPort(unsigned int port);


};
#endif // NETWORK_ANALYSER_H
