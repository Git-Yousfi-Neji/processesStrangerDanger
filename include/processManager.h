#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <string.h>
#include <dirent.h>
#include <cstdlib>
#include "xml_parser.h"
#include "../config/config.h"


struct SProcessInfo {
    char name[PROCESS_MANAGER_MAX_USER_SIZE];
    char umask[PROCESS_MANAGER_MAX_UMASK_SIZE ];
    char state;
    int tgid;
    int ppid;
    int pid;
    int tracerPid;
    int uid;
    int gid;
    int fdSize;
    int threads;
    double cpuUsage = 0;
    // extensible for other informations
};

class CProcessManager
{
	public:
		CProcessManager();
		void fillRunningProcessesInfos(struct SProcessInfo *info, int processID);
		void displayProcessInfo(const struct SProcessInfo *info);
		int  countAndStoreProcesses(int *processIds);
        bool isLegitimateProcessName(const struct SProcessInfo *processInfo, const char *filePath);
        void fillCPUUsage(int pid, struct SProcessInfo *processInfo);
        bool isHighCPUUsage(const struct SProcessInfo *processInfo);
        bool isUnexpectedPPID(int ppid, const int* expectedPPIDs);
        bool isAbnormalNumThreads(int numThreads);
};

#endif // PROCESS_MANAGER_H
