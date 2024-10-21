#pragma GCC optimize(2)
#include <stdio.h>
#include <sysinfoapi.h>

int main() {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    puts(__FILE__);
    if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) {
        printf("X64(AMD or Intel)\n");
    } else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM) {
        printf("AMD\n");
    } else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) {
        printf("Intel\n");
    } else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) {
        printf("X86\n");
    } else {
        printf("undefined struct\n");
    }

    return 0;
}