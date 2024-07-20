// Permissions.h
#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#pragma comment(lib, "advapi32.lib")

#include <vector>
#include <windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <stdio.h>
#include <memoryapi.h>
#include <cstdio>
#include <fstream>
#include <string>

class Permissions {
public:
    static bool EnableDebugPrivilege();
};

#endif // PERMISSIONS_H
