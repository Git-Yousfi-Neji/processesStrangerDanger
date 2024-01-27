#include "../include/processManager.h"
#include <iostream>

int main() {
    struct SProcessInfo info;
    CProcessManager processManager;
    processManager.getRunningProcessesInfos(&info, 66);

    
    printf("Name: %s\n", info.name);
    printf("Umask: %s\n", info.umask);
    printf("State: %c\n", info.state);
    printf("Tgid: %d\n", info.tgid);
    printf("threads: %d\n", info.threads);

    return 0;
}
