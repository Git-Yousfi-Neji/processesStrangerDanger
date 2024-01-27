#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <string.h>

#define MAX_USER_NAME 50
#define MAX_PROCESS_NAME 50
#define MAX_PROCESSES_COUNT 10
#define MAX_CMD_SIZE 100
#define MAX_LINE_SIZE 100


/*
cat /proc/<processID>/status
will give informations like
| Parameter                   | Description/Hint                                      |
|-----------------------------|--------------------------------------------------------|
| Name                        | Name of the process                                   |
| Umask                       | Default file permission mask                          |
| State                       | Current state of the process (e.g., sleeping)        |
| Tgid                        | Thread group ID (same as PID)                         |
| Pid                         | Process ID                                            |
| PPid                        | Parent process ID                                     |
| TracerPid                   | PID of the process tracing this one (0 if none)      |
| Uid/Gid                     | User and group IDs of the process                     |
| FDSize                      | Maximum number of file descriptors                    |
| Threads                     | Number of threads in the process                      |
| Cpus_allowed                | Bitmask for allowed CPUs                              |
| Cpus_allowed_list           | List of CPUs allowed for the process                  |
| Mems_allowed                | Bitmask for allowed memory nodes (NUMA nodes)         |
| Mems_allowed_list           | List of memory nodes allowed for the process          |
| voluntary_ctxt_switches     | Number of voluntary context switches                 |
| nonvoluntary_ctxt_switches  | Number of non-voluntary context switches             |
*/

struct SProcessInfo {
    char name[50];
    char umask[5];
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

class CProcessManager {
public:
    CProcessManager();
    void getRunningProcessesInfos(struct SProcessInfo *info, int processID);
};

#endif // PROCESS_MANAGER_H
