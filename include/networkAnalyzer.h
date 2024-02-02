
#ifndef NETWORK_ANALYSER_H
#define NETWORK_ANALYSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

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
    std::string localPort; // Add localPort member
    std::string remotePort; // Add remotePort member
    // Add other members as needed.
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
    std::string localPort; // Add localPort member
    std::string remotePort; // Add remotePort member
    // Add other members as needed.
};

// Structure to hold Unix domain socket information.
struct SUnixInfo
{
    std::string socketType;  // e.g., "DGRAM", "STREAM"
    std::string socketPath;
    // Add other members as needed.
};

// Structure to hold overall network information.
struct SNetworkInfo
{
    struct STcpInfo _tcp;
    struct SUdpInfo _udp;
    struct SUnixInfo _unix;
    // Add other members as needed.
};


class CNetworkAnalyzer
{
	public:
		CNetworkAnalyzer();
		void fillNetworkInfo(const int pid, struct SNetworkInfo *networkInfo);
		bool isUnusualNetworkConnection(const struct SNetworkInfo *networkInfo);
		void displayNetworkInfos(const struct SNetworkInfo *net);
	private:
		STcpInfo fillTcpInfo(const int pid);
		SUdpInfo fillUdpInfo(const int pid);
		SUnixInfo fillUnixInfo(const int pid);


};
#endif // NETWORK_ANALYSER_H
