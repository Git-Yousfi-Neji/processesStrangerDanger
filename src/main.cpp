
#include "../include/processManager.h"
#include "../include/networkAnalyzer.h"
#include "../include/xml_parser.h"
const char *filePath = "data/systemUsernames.xml";


int main()
{
    CProcessManager processManager;
    CNetworkAnalyzer networkAnalyzer;
    
    int expectedPPIDs[PROCESS_MANAGER_LEGITIMATE_PPIDS_NUM] = {PROCESS_MANAGER_LEGITIMATE_PPIDS};

    int processIds[PROCESS_MANAGER_MAX_PROCESSES];
    int totalProcesses = processManager.countAndStoreProcesses(processIds);
    
    struct SProcessInfo processInfos;
    struct SNetworkInfo networkInfos;

    for (int i = 0; i < totalProcesses; i++)
    {
    	processManager.fillRunningProcessesInfos(&processInfos, processIds[i]);
    	processManager.fillCPUUsage(processIds[i], &processInfos);
    	networkAnalyzer.fillNetworkInfo(processIds[i], &networkInfos);

    	if ( !processManager.isLegitimateProcessName(&processInfos, filePath) ||
    	      processManager.isUnexpectedPPID(processInfos.ppid, expectedPPIDs) ||
     	     processManager.isHighCPUUsage(&processInfos) ||
     	     processManager.isAbnormalNumThreads(processInfos.threads) )
    	{
    		processManager.displayProcessInfo(&processInfos);
    		networkAnalyzer.displayNetworkInfos(&networkInfos);
    		printf ("Not Legitimate process\n");
		}
		else
		{
    		processManager.displayProcessInfo(&processInfos);
    		networkAnalyzer.displayNetworkInfos(&networkInfos);
    		printf ("Legitimate process\n");
		}
    }

    return 0;

}
