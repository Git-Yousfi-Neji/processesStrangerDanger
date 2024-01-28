#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <string.h>
#include <dirent.h>
#include <cstdlib>
#include "xml_parser.h"


#define MAX_UMASK_SIZE            5
#define MAX_USER_SIZE             50
#define MAX_PROCESS_NAME          50
#define MAX_PROCESSES_COUNT       10
#define MAX_CMD_SIZE              100
#define MAX_LINE_SIZE             1024
#define MAX_PROCESSES             1000
#define MAX_SYSTEM_USERNAMES_NUM  17  
#define PROC_DIR                  "/proc"

struct SProcessInfo {
    char name[MAX_USER_SIZE];
    char umask[MAX_UMASK_SIZE ];
    char state;
    int tgid;
    int ppid;
    int pid;
    int tracerPid;
    int uid;
    int gid;
    int fdSize;
    int threads;
    // extensible for other informations
};

class CProcessManager
{
	public:
		CProcessManager();
		void getRunningProcessesInfos(struct SProcessInfo *info, int processID);
		void displayProcessInfo(const struct SProcessInfo *info, const int processID);
		int  countAndStoreProcesses(int* processIds);
        bool isLegitimateProcess(const struct SProcessInfo* processInfo, const char *filePath);
};

#endif // PROCESS_MANAGER_H
