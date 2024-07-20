// Recall.h
#ifndef RECALL_H
#define RECALL_H

#include <windows.h>
#include <vector>
#include <string>

class Recall {
public:
    Recall(const std::wstring& processName);
    ~Recall();
    static HANDLE GetHandle(const wchar_t* procName);
    static DWORD GetProcId(const wchar_t* procName);
    static uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* procName);
    static uintptr_t FindDMAaddress(HANDLE hProc, uintptr_t baseAddr, const std::vector<unsigned int>& offsets);

    bool ReadMemory(LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize);
    template<typename T>
    T ReadMemory(LPCVOID lpBaseAddress);

private:
    std::wstring processName;
    HANDLE hProcess;
    DWORD procId;
};

#endif // RECALL_H
