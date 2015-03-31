/*
 * gurumin-pad
 * Copyright (C) 2015 Daniel Bloemendal. All rights reserved.
 *
 * Entry point for the proxy DInput8.dll library.
 */

#include "proxy.hpp"

namespace proxy {
    //
    // Globals
    //
    HMODULE library_dinput8;
    PVOID   exports_dinput8[5];

    VOID __declspec(noreturn) error() {
        // Get windows error code
        DWORD code = GetLastError();

        // Format the error code
        PVOID buffer = NULL;
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            code,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPWSTR)&buffer,
            0, NULL
            );

        // Process the message
        if (buffer) {
            MessageBox(NULL, (LPWSTR)buffer, PROJECT_TITLE, MB_SYSTEMMODAL | MB_ICONSTOP);
            LocalFree(buffer);
        }

        // Bail out
        TerminateProcess(GetCurrentProcess(), code);
    }

    VOID init() {
        //
        // Load original system DINPUT8 library
        //

        // Fetch system directory
        WCHAR path_system[MAX_PATH];
        if (GetSystemDirectory(path_system, ARRAYSIZE(path_system)) == 0) error();

        // Prepare DINPUT8 path
        std::wstringstream ss;
        ss << path_system << L"\\dinput8.dll";
        std::wstring path_dinput8 = ss.str();

        // Load library
        library_dinput8 = LoadLibrary(path_dinput8.c_str());
        if (!library_dinput8) error();

        //
        // Fetch required procedures
        //

        exports_dinput8[0] = GetProcAddress(library_dinput8, "DirectInput8Create"); if (!exports_dinput8[0]) error();
        exports_dinput8[1] = GetProcAddress(library_dinput8, "DllCanUnloadNow"); if (!exports_dinput8[1]) error();
        exports_dinput8[2] = GetProcAddress(library_dinput8, "DllGetClassObject"); if (!exports_dinput8[2]) error();
        exports_dinput8[3] = GetProcAddress(library_dinput8, "DllRegisterServer"); if (!exports_dinput8[3]) error();
        exports_dinput8[4] = GetProcAddress(library_dinput8, "DllUnregisterServer"); if (!exports_dinput8[4]) error();
    }

    VOID exit() {
        if (library_dinput8) {
            FreeLibrary(library_dinput8);
            library_dinput8 = NULL;
        }
    }
}

extern "C"
{
    typedef HRESULT WINAPI PROC_DIRECTINPUT8CREATE(
        HINSTANCE hinst,
        DWORD dwVersion,
        REFIID riidltf,
        LPVOID * ppvOut,
        LPUNKNOWN punkOuter);

    HRESULT WINAPI proxy_DirectInput8Create(
        HINSTANCE hinst,
        DWORD dwVersion,
        REFIID riidltf,
        LPVOID * ppvOut,
        LPUNKNOWN punkOuter)
    {
        PROC_DIRECTINPUT8CREATE* di8create
            = (PROC_DIRECTINPUT8CREATE*) proxy::exports_dinput8[0];

        return di8create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
    }

    HRESULT __declspec(naked) WINAPI proxy_DllCanUnloadNow() {
        __asm jmp proxy::exports_dinput8[1]
    }

    HRESULT __declspec(naked) WINAPI proxy_DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv) {
        __asm jmp proxy::exports_dinput8[2]
    }

    HRESULT __declspec(naked) WINAPI proxy_DllRegisterServer() {
        __asm jmp proxy::exports_dinput8[3]
    }

    HRESULT __declspec(naked) WINAPI proxy_DllUnregisterServer() {
        __asm jmp proxy::exports_dinput8[4]
    }
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpvReserved
    )
{
    if (fdwReason == DLL_PROCESS_ATTACH)
        proxy::init();
    else if (fdwReason == DLL_PROCESS_DETACH)
        proxy::exit();

    return TRUE;
}
