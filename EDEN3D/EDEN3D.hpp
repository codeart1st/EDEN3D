#pragma once

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef EDEN3D_EXPORTS
#define EDEN3D_API __declspec(dllexport)
#else
#define EDEN3D_API __declspec(dllimport)
#endif
