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
		void getRunningProcessesInfos(struct SProcessInfo *info, int processID);
		void displayProcessInfo(const struct SProcessInfo *info);
		int  countAndStoreProcesses(int* processIds);
        bool isLegitimateProcess(const struct SProcessInfo* processInfo, const char *filePath);
        void cpuUsage(int pid, struct SProcessInfo *processInfo);
};

#endif // PROCESS_MANAGER_H
