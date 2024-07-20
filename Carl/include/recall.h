#pragma once
// Recall.h
#ifndef RECALL_H
#define RECALL_H

#include <windows.h>
#include <vector>

class Recall {
public:
    Recall(DWORD pid);
    ~Recall();
    bool ReadMemory(LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize);
    template<typename T>
    T ReadMemory(LPCVOID lpBaseAddress);

private:
    HANDLE hProcess;
};

#endif // RECALL_H
