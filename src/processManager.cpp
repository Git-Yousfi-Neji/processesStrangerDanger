
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string.h>

#include "../include/processManager.h"

#define PARSE_PARAM(line, format, variable) (sscanf(line, format, &variable) == 1) {}

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
    char path[MAX_CMD_SIZE];
    snprintf(path, MAX_CMD_SIZE, "/proc/%d/status", processID);
    
    FILE *file = fopen(path, "r");
    
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_SIZE];

    while (fgets(line, MAX_LINE_SIZE, file) != NULL)
    {
        if      PARSE_PARAM(line, "Name:\t%s", info->name)
        else if PARSE_PARAM(line, "Umask:\t%s", info->umask)
        else if PARSE_PARAM(line, "State:\t%c", info->state)
        else if PARSE_PARAM(line, "Tgid:\t%d", info->tgid)
        else if PARSE_PARAM(line, "PPid:\t%d", info->ppid)
        else if PARSE_PARAM(line, "Pid:\t%d", info->pid)
        else if PARSE_PARAM(line, "TracerPid:\t%d", info->tracerPid)
        else if PARSE_PARAM(line, "Uid:\t%d", info->uid)
        else if PARSE_PARAM(line, "Gid:\t%d", info->gid)
        else if PARSE_PARAM(line, "FDSize:\t%d", info->fdSize)
        else if PARSE_PARAM(line, "Threads:\t%d", info->threads)
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
void CProcessManager::displayProcessInfo(const struct SProcessInfo *info, const int processID)
{
	printf("Name:\t%s\n", info->name);
	printf("Umask:\t%s\n", info->umask);
	printf("State:\t%c\n", info->state);
	printf("Tgid:\t%d\n", info->tgid);
    printf("PPid:\t%d\n", info->ppid);
    printf("Pid:\t%d\n", info->pid);
    printf("TracerPid:\t%d\n", info->tracerPid);
    printf("Uid:\t%d\n", info->uid);
    printf("Gid:\t%d\n", info->gid);
    printf("FDSize:\t%d\n", info->fdSize);
    printf("Threads:\t%d\n", info->threads);
}

/** @brief Function to count and store all processes PIDs in
 *         the processIds array
 *
 *  @param processIds a reference on the the array to hols all PIDs
 *  @return int the count of running processes
 */
int CProcessManager::countAndStoreProcesses(int* processIds)
{
    DIR *procDir = opendir(PROC_DIR);
    struct dirent *entry;
    int processCount = 0;

    if (procDir == NULL)
    {
        perror("Error opening /proc directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(procDir)) != NULL)
    {
    	if (entry->d_type == DT_DIR && atoi(entry->d_name) != 0)
        {
            int pid = atoi(entry->d_name);
            processIds[processCount] = pid;
            processCount++;
            
            if (processCount >= MAX_PROCESSES)
            {
                fprintf(stderr, "Too many processes to handle. Increase MAX_PROCESSES.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    closedir(procDir);
    return processCount;
}