// - stdio.h: для работы с функциями ввода/вывода (printf)
// - windows.h: для использования Windows API (создание процессов, pipes и т.д.)
// - fibonacci.h: наш собственный заголовочный файл с объявлением функции fibonacci
#include <stdio.h>
#include <windows.h>
#include "fibonacci.h"

int main() {
    // hReadPipe - дескриптор для чтения из канала
    // hWritePipe - дескриптор для записи в канал
    // sa - атрибуты безопасности (размер структуры, наследование дескрипторов)
    HANDLE hReadPipe, hWritePipe;
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);

    // si - структура с информацией для старта процесса
    // pi - структура для хранения информации о созданном процессе
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    
    // Командная строка для запуска дочернего процесса
    // L указывает на использование wide-char (Unicode) строки
    wchar_t cmdline[] = L"child.exe";

    // Настройка перенаправления вывода дочернего процесса в наш pipe
    si.hStdOutput = hWritePipe;  // Перенаправляем stdout дочернего процесса
    si.dwFlags = STARTF_USESTDHANDLES;  // Флаг, указывающий на использование перенаправления

    // CreateProcessW - Unicode-версия функции для создания процесса
    CreateProcessW(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

    // Родительский процесс вычисляет 6-е число Фибоначчи
    unsigned long long parent_result = fibonacci(6);
    printf("[PARENT] F(6) = %llu\n", parent_result);

    //Закрытие ненужного дескриптора записи. После запуска дочернего процесса, родителю он больше не нужен
    CloseHandle(hWritePipe);

    // Чтение вывода из дочернего процесса
    char buffer[100];  // Буфер для чтения данных
    DWORD bytesRead;   // Количество прочитанных байт
    // Читаем данные из pipe пока они есть
    while (ReadFile(hReadPipe, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead != 0) {
        printf("%.*s", (int)bytesRead, buffer);  // Выводим прочитанные данные
    }

    // Завершение работы - закрытие всех дескрипторов
    CloseHandle(hReadPipe);         // Закрываем дескриптор чтения
    CloseHandle(pi.hProcess);       // Закрываем дескриптор процесса
    CloseHandle(pi.hThread);        // Закрываем дескриптор потока
    
    return 0;
}