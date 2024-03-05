#pragma once
#include <windows.h>

static inline bool IsDedicatedServer(void) {
    static int cached_result = -1; // Initially unset
    if (cached_result == -1) {
        char path[MAX_PATH];
        if (GetModuleFileNameA(NULL, path, MAX_PATH)) {
            // Extract the executable name from the path
            char* exeName = strrchr(path, '\\') ? strrchr(path, '\\') + 1 : path;

            // Compare the executable name with "r1ds.exe"
            if (_stricmp(exeName, "r1ds.exe") == 0) {
                cached_result = 1;
            }
            else {
                cached_result = 0;
            }
        }
        else {
            // If GetModuleFileNameA fails, assume it's not a dedicated server.
            cached_result = 0;
        }
    }
    return cached_result == 1 ? true : false;
}
#define ENGINE_DLL (IsDedicatedServer() ? "engine_ds.dll" : "engine.dll")
#define VSCRIPT_DLL (IsDedicatedServer() ? "dedicated.dll" : "launcher.dll")
