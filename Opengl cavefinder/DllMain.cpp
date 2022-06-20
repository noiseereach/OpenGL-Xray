#include "DllMain.h"
//https://www.youtube.com/c/NoiseReach
T_wglSwapBuffers pSwapBuffers = nullptr;

BOOL __stdcall mySwapBuffers(HDC hDC)
{
	if (GetAsyncKeyState(0x58) & 1) {
		xray = !xray;
	}

	glDepthFunc(GL_LEQUAL);

	if (xray) {
		glDepthFunc(GL_ALWAYS);
	}

	return pSwapBuffers(hDC);
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		HMODULE hModd = GetModuleHandleW(L"OpenGL32.dll");

		if (!hModd)
		{
			return FALSE;
		}

		pSwapBuffers = reinterpret_cast<T_wglSwapBuffers>(GetProcAddress(hModd, "wglSwapBuffers"));

		DetourRestoreAfterWith();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(reinterpret_cast<void**>(&pSwapBuffers), mySwapBuffers);
		return DetourTransactionCommit() == NO_ERROR;

	}

	break;

	case DLL_PROCESS_DETACH:
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(reinterpret_cast<void**>(&pSwapBuffers), mySwapBuffers);
		return DetourTransactionCommit() == NO_ERROR;
	}

	}

	return TRUE;
}

