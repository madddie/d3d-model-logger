#include "Hook.h"
#include "Tools.h"
#include "Render.h"
#include "SDK.h"
#include "ModelRec.h"
CSDK*		SDK = new CSDK;
CRender*	Render = new CRender;

long __stdcall CHook::HookedDIP(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount)
{
	LPDIRECT3DVERTEXBUFFER9 StreamData;

	UINT Offset = 0;
	UINT Stride = 0;

	if (pDevice->GetStreamSource(0, &StreamData, &Offset, &Stride) == D3D_OK)
		StreamData->Release();

	if (Stride == SDK->StrideCoefficient)
	{
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		
		pDevice->SetTexture(0, Render->Green);

		DrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, StartIndex, PrimitiveCount);

		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}
	if (NumVertices == SDK->NumVerticesCoefficient)
	{
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

		pDevice->SetTexture(0, Render->Green);

		DrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, StartIndex, PrimitiveCount);

		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}
	if (PrimitiveCount == SDK->PrimCountCoefficient)
	{
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

		pDevice->SetTexture(0, Render->Green);

		DrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, StartIndex, PrimitiveCount);

		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}

	return DrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, StartIndex, PrimitiveCount);
}

long __stdcall CHook::HookedEndScene(LPDIRECT3DDEVICE9 pDevice)
{

	static bool Init = false;
	if (!Init)
	{
		D3DXCreateFont(pDevice, 12, 0, FW_DONTCARE, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &Render->Font);
		
		D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&GreenTexture, 60, &Render->Green);
		
		Init = true;
	}

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	SDK->Frame(pDevice);

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return EndScene(pDevice);
}

void CHook::Start()
{
	std::cout << "finding:\n";

	std::cout << "\td3d9.dll";
	D3D9Dll = DWORD(GetModuleHandle("d3d9.dll"));
	std::cout << "...done\n";

	std::cout << "\td3ddevice";
	D3DBase = Tools->FindPattern((PUCHAR)D3D9Dll, 0x128000, (PCUCHAR)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", (PCCHAR)"xx????xx????xx");
	std::cout << "...done\n";

	std::cout << "\td3dvmt";
	D3DVMT = *(DWORD**)(D3DBase + 2);
	std::cout << "...done\n";

	Hook();
}

void CHook::VMTHook(void* Function, void* Hook)
{
	/* get old protection */
	DWORD OldProtect;

	/* vprotect the page we want to edit */
	VirtualProtect(Function, 4, PAGE_EXECUTE_READWRITE, &OldProtect);

	/* write at function ptr a ptr to our own function */
	memcpy(Function, &Hook, 4);

	/* reassign protection to page in mem */
	VirtualProtect(Function, 4, OldProtect, &OldProtect);
}

void CHook::Hook()
{
	DrawIndexedPrimitive = (oDrawIndexedPrimitive)(DWORD)D3DVMT[82];
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)DrawIndexedPrimitive, HookedDIP);
	DetourTransactionCommit();

	EndScene = (oEndScene)(DWORD)D3DVMT[42];
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)EndScene, HookedEndScene);
	DetourTransactionCommit();
}