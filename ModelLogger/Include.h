#pragma once

#define _USE_MATH_DEFINES
#define GETKEY(key) GetAsyncKeyState(key) & 1

#include <Windows.h>
#include <iostream>
#include <io.h>
#include <string>
#include <cmath> 

#include <d3d9.h>
#include <d3dx9.h>
#include <dwmapi.h>
#include <detours.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "detours.lib")

#pragma warning	(disable: 4244) 
#pragma warning	(disable: 4996) 
#pragma warning (disable: 4312) 
#pragma warning (disable: 4311) 
#pragma warning (disable: 4099)
#pragma warning (disable: 4005)

#define WHITE(alpha)         D3DCOLOR_ARGB(alpha, 255, 255, 255)
#define BLACK(alpha)         D3DCOLOR_ARGB(alpha, 0, 0, 0)
#define RED(alpha)           D3DCOLOR_ARGB(alpha, 255, 0, 0)
#define GREEN(alpha)         D3DCOLOR_ARGB(alpha, 0, 128, 0)
#define LAWNGREEN(alpha)     D3DCOLOR_ARGB(alpha, 124, 252, 0)
#define BLUE(alpha)          D3DCOLOR_ARGB(alpha, 0, 200, 255)
#define DEEPSKYBLUE(alpha)   D3DCOLOR_ARGB(alpha, 0, 191, 255)
#define SKYBLUE(alpha)       D3DCOLOR_ARGB(alpha, 0, 122, 204)
#define YELLOW(alpha)        D3DCOLOR_ARGB(alpha, 255, 255, 0)
#define ORANGE(alpha)        D3DCOLOR_ARGB(alpha, 255, 165, 0)
#define DARKORANGE(alpha)    D3DCOLOR_ARGB(alpha, 255, 140, 0)
#define PURPLE(alpha)        D3DCOLOR_ARGB(alpha, 125, 0, 255)
#define CYAN(alpha)          D3DCOLOR_ARGB(alpha, 0, 255, 255)
#define PINK(alpha)          D3DCOLOR_ARGB(alpha, 255, 20, 147)
#define GRAY(alpha)          D3DCOLOR_ARGB(alpha, 128, 128, 128)
#define DARKGRAY(alpha)      D3DCOLOR_ARGB(alpha, 73, 73, 73)
#define DARKERGRAY(alpha)    D3DCOLOR_ARGB(alpha, 31, 31, 31)

typedef const unsigned char* PCUCHAR;
typedef const char* PCCHAR;