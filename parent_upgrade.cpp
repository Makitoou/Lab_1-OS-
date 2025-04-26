#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "fibonacci.h"

struct SharedData {
    unsigned long long parentResult;
    unsigned long long childResult;
};

int main() {
    // Создание разделяемой памяти
    const wchar_t* MEM_NAME = L"Global\\FibonacciMem";
    const wchar_t* MUTEX_NAME = L"Global\\FibonacciMutex";

    HANDLE hMapFile = CreateFileMappingW(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(SharedData),
        MEM_NAME
    );
    if (!hMapFile) {
        printf("[PARENT] CreateFileMapping failed (%lu)\n", GetLastError());
        return 1;
    }

    SharedData* sharedData = (SharedData*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedData));
    if (!sharedData) {
        printf("[PARENT] MapViewOfFile failed (%lu)\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Инициализация мьютекса
    HANDLE hMutex = CreateMutexW(NULL, FALSE, MUTEX_NAME);
    if (!hMutex) {
        printf("[PARENT] CreateMutex failed (%lu)\n", GetLastError());
        UnmapViewOfFile(sharedData);
        CloseHandle(hMapFile);
        return 1;
    }

    // Запуск дочернего процесса
    wchar_t cmdline[256];
    swprintf(cmdline, 256, L"child.exe %s %s", MEM_NAME, MUTEX_NAME);

    STARTUPINFOW si = { sizeof(STARTUPINFOW) };
    PROCESS_INFORMATION pi;
    if (!CreateProcessW(
        NULL, cmdline, NULL, NULL, TRUE, 0,
        NULL, NULL, &si, &pi
    )) {
        printf("[PARENT] CreateProcess failed (%lu)\n", GetLastError());
        CloseHandle(hMapFile);
        CloseHandle(hMutex);
        return 1;
    }

    // Вычисление и запись родительского результата
    unsigned long long parent_result = fibonacci(6);
    WaitForSingleObject(hMutex, INFINITE);
    sharedData->parentResult = parent_result;
    ReleaseMutex(hMutex);

    // Ожидание завершения дочернего процесса
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Вывод результатов
    printf("[PARENT] Parent result: %llu\n", sharedData->parentResult);
    printf("[PARENT] Child result: %llu\n", sharedData->childResult);

    // Очистка
    UnmapViewOfFile(sharedData);
    CloseHandle(hMapFile);
    CloseHandle(hMutex);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}