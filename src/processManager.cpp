#include "../include/processManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string.h>

#define PARSE_PARAM(line, format, variable) (sscanf(line, format, &variable) == 1) {}

CProcessManager::CProcessManager() {
    // Constructor implementation (if needed)
}
void CProcessManager::getRunningProcessesInfos(struct SProcessInfo *info, int processID)
{
    char path[MAX_CMD_SIZE];
    snprintf(path, MAX_CMD_SIZE, "/proc/%d/status", processID);
    printf("path=%s\n",path);
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