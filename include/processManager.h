#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <string.h>
#include <dirent.h>
#include <cstdlib>
#include "xml_parser.h"


#define PROCESS_MANAGER_MAX_UMASK_SIZE            5
#define PROCESS_MANAGER_MAX_USER_SIZE             50
#define PROCESS_MANAGER_MAX_PROCESS_NAME          50
#define PROCESS_MANAGER_MAX_PROCESSES_COUNT       10
#define PROCESS_MANAGER_MAX_BUFFER_SIZE           256
#define PROCESS_MANAGER_MAX_CMD_SIZE              1024
#define PROCESS_MANAGER_MAX_LINE_SIZE             1024
#define PROCESS_MANAGER_MAX_PROCESSES             1000
#define PROCESS_MANAGER_UID_THRESHOLD             1000
#define PROCESS_MANAGER_MAX_SYSTEM_USERNAMES_NUM  17  
#define PROCESS_MANAGER_PROC_DIR                  "/proc"
#define PROCESS_MANAGER_CPU_USAGE_SCRIPT          "scripts/total_cpu_usage.sh"

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
