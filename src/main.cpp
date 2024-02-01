
#include "../include/processManager.h"
#include "../include/xml_parser.h"
const char *filePath = "data/systemUsernames.xml";

int main()
{
    CProcessManager processManager;

    int processIds[PROCESS_MANAGER_MAX_PROCESSES];
    int totalProcesses = processManager.countAndStoreProcesses(processIds);
    struct SProcessInfo info;

    for (int i = 0; i < totalProcesses; i++)
    {
    	processManager.getRunningProcessesInfos(&info, processIds[i]);

    	if (info.uid >= PROCESS_MANAGER_UID_THRESHOLD)
    	{
    		if (processManager.isLegitimateProcess(&info, filePath))
    		{
                processManager.cpuUsage(processIds[i], &info);
    			processManager.displayProcessInfo(&info);
    			printf("Legitimate\n");
    		}
    		else
    		{
                processManager.cpuUsage(processIds[i], &info);
                processManager.displayProcessInfo(&info);
                printf("Not Legitimate\n");
            }
		}
    }

    return 0;

}
