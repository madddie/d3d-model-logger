#include "Include.h"
#include "Hook.h"
#include "Tools.h"
#include "Render.h"

CTools*		Tools = new CTools;
CHook*		Hook = new CHook;

void __stdcall Routine()
{
	Tools->Start();

	std::cout << "initializing...\n";

	Tools->WriteLog("[ Maddie D3D Model Logger - %s ]\n", Tools->StartTime);

	Hook->Start();

	std::cout << "finished...\n"; 

	return;
}

bool __stdcall DllMain(HMODULE Instance, DWORD Reason, LPVOID Reserved)
{
	if (Reason == 1)
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Routine, 0, 0, 0);
		
	return true;
}