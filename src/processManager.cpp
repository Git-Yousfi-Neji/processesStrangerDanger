
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string.h>

#include "../include/processManager.h"

CProcessManager::CProcessManager()
{
}

/** @brief Function to get informations about a process
 *         based on its PID
 *
 *  @param info a pointer to a struct to hold process informations
 *  @param processID the PID of the process
 *  @return Void
 */
void CProcessManager::getRunningProcessesInfos(struct SProcessInfo *info, int processID)
{
    char path[PROCESS_MANAGER_MAX_CMD_SIZE];
    snprintf(path, PROCESS_MANAGER_MAX_CMD_SIZE, "/proc/%d/status", processID);
    
    FILE *file = fopen(path, "r");
    
    if (file == NULL)
    {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    char line[PROCESS_MANAGER_MAX_LINE_SIZE];

    while (fgets(line, PROCESS_MANAGER_MAX_LINE_SIZE, file) != NULL)
    {
        if      (sscanf(line, "Name:\t%s", info->name) == 1) {}
        else if (sscanf(line, "Umask:\t%s", info->umask) == 1) {}
        else if (sscanf(line, "State:\t%c", &info->state) == 1) {}
        else if (sscanf(line, "Tgid:\t%d", &info->tgid) == 1) {}
        else if (sscanf(line, "PPid:\t%d", &info->ppid) == 1) {}
        else if (sscanf(line, "Pid:\t%d", &info->pid) == 1) {}
        else if (sscanf(line, "TracerPid:\t%d", &info->tracerPid) == 1) {}
        else if (sscanf(line, "Uid:\t%d", &info->uid) == 1) {}
        else if (sscanf(line, "Gid:\t%d", &info->gid) == 1) {}
        else if (sscanf(line, "FDSize:\t%d", &info->fdSize) == 1) {}
        else if (sscanf(line, "Threads:\t%d", &info->threads) == 1) {}
    }
    fclose(file);
}

/** @brief Function to display the informations about the process
 *         based on its PID
 *
 *  @param info a pointer to a struct that holds the process informations
 *  @param processID the PID of the process
 *  @return Void
 */
void CProcessManager::displayProcessInfo(const struct SProcessInfo *info)
{
    printf("=========== PROC %d INFOS =========\n", info->pid);
	printf("| Name:\t%s\n", info->name);
	printf("| Umask:\t%s\n", info->umask);
	printf("| State:\t%c\n", info->state);
	printf("| Tgid:\t%d\n", info->tgid);
    printf("| PPid:\t%d\n", info->ppid);
    printf("| Pid:\t%d\n", info->pid);
    printf("| TracerPid:\t%d\n", info->tracerPid);
    printf("| Uid:\t%d\n", info->uid);
    printf("| Gid:\t%d\n", info->gid);
    printf("| FDSize:\t%d\n", info->fdSize);
    printf("| Threads:\t%d\n", info->threads);
    printf("| CPU usage:\t%lf\n", info->cpuUsage);
    printf("========================================\n");
}

/** @brief Function to count and store all processes PIDs in
 *         the processIds array
 *
 *  @param processIds a reference on the the array to hols all PIDs
 *  @return int the count of running processes
 */
int CProcessManager::countAndStoreProcesses(int* processIds)
{
    DIR *procDir = opendir(PROCESS_MANAGER_PROC_DIR);
    struct dirent *entry;
    int processCount = 0;

    if (procDir == NULL)
    {
        perror("Error opening /proc directory\n");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(procDir)) != NULL)
    {
    	if (entry->d_type == DT_DIR && atoi(entry->d_name) != 0)
        {
            int pid = atoi(entry->d_name);
            processIds[processCount] = pid;
            processCount++;
            
            if (processCount >= PROCESS_MANAGER_MAX_PROCESSES)
            {
                fprintf(stderr, "Too many processes to handle. Increase PROCESS_MANAGER_MAX_PROCESSES.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    closedir(procDir);
    return processCount;
}

/** @brief Function to return true if the process is in legitim list
 *         or false if not
 *
 *  @param processInfo a reference on the processes informations
 *  @param filePath file path of the legitimate list
 *  @return bool true if legitimate false if not
 */
bool CProcessManager::isLegitimateProcess(const struct SProcessInfo* processInfo, const char *filePath)
{
    SystemUsernamesList userList = parseSystemUsernames(filePath);
    int numSystemUsernames = userList.count;
    
    for (int i = 0; i < numSystemUsernames; ++i)
    {
        if (strcmp(processInfo->name, userList.usernames[i]) == 0)
        {
            freeSystemUsernamesList(&userList);
            return true;
        }
    }
    freeSystemUsernamesList(&userList);
    return false;
}

void CProcessManager::cpuUsage(int pid, struct SProcessInfo *processInfo)
{
    char command[PROCESS_MANAGER_MAX_CMD_SIZE];
    snprintf(command, sizeof(command), "/bin/bash %s %d",PROCESS_MANAGER_CPU_USAGE_SCRIPT, pid);

    FILE *pipe = popen(command, "r");
    if (pipe == NULL)
    {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    char buffer[PROCESS_MANAGER_MAX_BUFFER_SIZE];
    while (fgets(buffer, PROCESS_MANAGER_MAX_BUFFER_SIZE, pipe) != NULL)
    {
        sscanf(buffer, "Used %lf%% of CPU", &(processInfo->cpuUsage));
    }

    if (pclose(pipe) == -1)
    {
        perror("pclose");
        exit(EXIT_FAILURE);
    }
}

