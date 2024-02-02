
#include "../include/processManager.h"
#include "../include/xml_parser.h"
const char *filePath = "data/systemUsernames.xml";


int main()
{
    CProcessManager processManager;
    int expectedPPIDs[18] = {PROCESS_MANAGER_EXPECTED_PPIDS};

    int processIds[PROCESS_MANAGER_MAX_PROCESSES];
    int totalProcesses = processManager.countAndStoreProcesses(processIds);
    struct SProcessInfo info;

    for (int i = 0; i < totalProcesses; i++)
    {
    	processManager.fillRunningProcessesInfos(&info, processIds[i]);
    	processManager.fillCPUUsage(processIds[i], &info);

    	if ( !processManager.isLegitimateProcessName(&info, filePath) ||
    	      processManager.isUnexpectedPPID(info.ppid, expectedPPIDs) ||
     	     processManager.isHighCPUUsage(&info) ||
     	     processManager.isAbnormalNumThreads(info.threads) )
    	{
    		processManager.displayProcessInfo(&info);
    		printf ("Not Legitimate process\n");
		}
		else
		{
    		processManager.displayProcessInfo(&info);
    		printf ("Legitimate process\n");
		}
    }

    return 0;

}
