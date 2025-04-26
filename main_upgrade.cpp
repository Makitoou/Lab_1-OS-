#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "fibonacci.h"

struct SharedData {
    unsigned long long parentResult;
    unsigned long long childResult;
};

int wmain(int argc, wchar_t* argv[]) {
    if (argc < 3) {
        printf("Usage: child.exe <SharedMemoryName> <MutexName>\n");
        return 1;
    }

    // Открытие разделяемой памяти
    HANDLE hMapFile = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, argv[1]);
    if (!hMapFile) {
        printf("[CHILD] OpenFileMapping failed (%lu)\n", GetLastError());
        return 1;
    }

    SharedData* sharedData = (SharedData*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedData));
    if (!sharedData) {
        printf("[CHILD] MapViewOfFile failed (%lu)\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Открытие мьютекса
    HANDLE hMutex = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, argv[2]);
    if (!hMutex) {
        printf("[CHILD] OpenMutex failed (%lu)\n", GetLastError());
        UnmapViewOfFile(sharedData);
        CloseHandle(hMapFile);
        return 1;
    }

    // Вычисление и запись результата
    unsigned long long result = fibonacci(6);

    WaitForSingleObject(hMutex, INFINITE);
    sharedData->childResult = result;
    ReleaseMutex(hMutex);

    // Очистка
    UnmapViewOfFile(sharedData);
    CloseHandle(hMapFile);
    CloseHandle(hMutex);

    return 0;
}