#include <Windows.h>
#include "framework.h"
#include "Detours.h"
#pragma comment(lib, "Detours32.lib")
#if defined _M_X64

#include "GLx64/glew.h"
#pragma comment(lib, "GLx64/glew32s.lib")
#elif defined _M_IX86
#include "GLx86/glew.h"
#pragma comment(lib, "GLx86/glew32s.lib")
#endif

bool xray = false;
typedef int(__stdcall* T_wglSwapBuffers)(HDC);