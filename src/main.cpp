
#include <iostream>

#include "../include/processManager.h"

int main()
{
    struct SProcessInfo info;
    CProcessManager processManager;
    
    int processIds[MAX_PROCESSES];
    int totalProcesses = processManager.countAndStoreProcesses(processIds);
    
    for(int i=0;i<totalProcesses;i++)
    {
    	processManager.getRunningProcessesInfos(&info, processIds[i]);
    	processManager.displayProcessInfo(&info, processIds[i]);
    	printf("=================================\n");
    }

    return 0;
    
}
