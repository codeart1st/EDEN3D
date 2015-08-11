#pragma once

#define WIN32_LEAN_AND_MEAN

#include <D3D11.h>
#include <D3DX11.h>
#include <DirectXMath.h>
#include <windows.h>

#include <string>
#include <vector>

using namespace DirectX;
using namespace std;

#ifdef EDEN3D_EXPORTS
#define EDEN3D_API __declspec(dllexport)
#else
#define EDEN3D_API __declspec(dllimport)
#endif
