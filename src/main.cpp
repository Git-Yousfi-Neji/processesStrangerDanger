
#include <iostream>

#include "../include/processManager.h"
#include "../include/xml_parser.h"
const char *filePath = "data/configs.xml";

int main()
{
    CProcessManager processManager;

    int processIds[MAX_PROCESSES];
    int totalProcesses = processManager.countAndStoreProcesses(processIds);
    struct SProcessInfo info;

    for (int i = 0; i < totalProcesses; i++)
    {
    	processManager.getRunningProcessesInfos(&info, processIds[i]);

    	if (info.uid >= 1000)
    	{
    		if (processManager.isLegitimateProcess(&info, filePath))
    		{
                processManager.cpuUsage(processIds[i], &info);
    			processManager.displayProcessInfo(&info, processIds[i]);
    			printf("Legitimate\n");
    		}
    		else
    		{
                processManager.cpuUsage(processIds[i], &info);
                processManager.displayProcessInfo(&info, processIds[i]);
                printf("Not Legitimate\n");
            }
		}
    }

    return 0;

}
