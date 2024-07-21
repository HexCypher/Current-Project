// EntityListParser.h
// Version: .001

#ifndef ENTITYLISTPARSER_H
#define ENTITYLISTPARSER_H

#include <windows.h>
#include <vector>

struct Entity {
    DWORD guid;
    float x, y, z;
};

class EntityListParser {
public:
    static std::vector<Entity> ParseEntityList(HANDLE hProcess, uintptr_t entityListBaseAddress);
};

#endif // ENTITYLISTPARSER_H
