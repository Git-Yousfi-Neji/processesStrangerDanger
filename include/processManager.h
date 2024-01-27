#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <vector>
#include <string>
#define MAX_USER_NAME 50
#define MAX_PROCESS_NAME 50
#define MAX_PROCESSES_COUNT 10

struct ProcessInfo {
    char name[MAX_PROCESS_NAME];
    char user[MAX_USER_NAME];
    int pid;
} ProcessInfo;

class CProcessManager {
public:
    CProcessManager();

    // Function to retrieve a list of running processes
    ProcessInfo getRunningProcessesInfos() const;

private:

};

#endif // PROCESS_MANAGER_H
