#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

#include "../include/processManager.h"
#include "../include/networkAnalyzer.h"
#include "../include/xml_parser.h"

const char *filePath = "data/systemUsernames.xml";

void processThread(int processId) {
    CProcessManager processManager;
    CNetworkAnalyzer networkAnalyzer;
    
    int expectedPPIDs[PROCESS_MANAGER_LEGITIMATE_PPIDS_NUM] = {PROCESS_MANAGER_LEGITIMATE_PPIDS};

    struct SProcessInfo processInfos;
    struct SNetworkInfo networkInfos;

    processManager.fillRunningProcessesInfos(&processInfos, processId);
    processManager.fillCPUUsage(processId, &processInfos);
    networkAnalyzer.fillNetworkInfo(processId, &networkInfos);

    if (!processManager.isLegitimateProcessName(&processInfos, filePath) &&
        processManager.isUnexpectedPPID(processInfos.ppid, expectedPPIDs) &&
        processManager.isHighCPUUsage(&processInfos) &&
        processManager.isAbnormalNumThreads(processInfos.threads) &&
        !networkAnalyzer.isLegitimateConnection(&networkInfos))
    {
        printf("PID:%d is NOT LEGITIMATE\n", processId); 
        processManager.displayProcessInfo(&processInfos);
        networkAnalyzer.displayNetworkInfos(processId, &networkInfos);
    }
    else
    {
    	/*
        printf("PID:%d is LEGITIMATE\n", processId);
        processManager.displayProcessInfo(&processInfos);
        networkAnalyzer.displayNetworkInfos(processId, &networkInfos);
        */
    }
    printf ("\n**********************************************\n\n");
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    CProcessManager processManager;
    
    int processIds[PROCESS_MANAGER_MAX_PROCESSES];
    int totalProcesses = processManager.countAndStoreProcesses(processIds);

    // Specify the number of threads you want to use
    const int numThreads = 8;  // Adjust this based on your system and workload

    std::vector<std::thread> threads;

    for (int i = 0; i < totalProcesses; i += numThreads) {
        // Launch threads, each handling a portion of the processes
        for (int j = 0; j < numThreads && i + j < totalProcesses; ++j) {
            threads.emplace_back(processThread, processIds[i + j]);
        }

        // Wait for threads to finish
        for (auto &thread : threads) {
            thread.join();
        }

        // Clear the threads vector for the next iteration
        threads.clear();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}
