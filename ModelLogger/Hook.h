#include "Include.h"

typedef HRESULT(WINAPI* oDrawIndexedPrimitive) (LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount);
typedef HRESULT(WINAPI* oEndScene) (LPDIRECT3DDEVICE9 pDevice);

static oDrawIndexedPrimitive	DrawIndexedPrimitive;
static oEndScene				EndScene;

class CHook
{
public:
	DWORD	D3D9Dll;
	DWORD	D3DBase;
	DWORD*	D3DVMT;

	static long __stdcall HookedDIP(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount);
	static long __stdcall HookedEndScene(LPDIRECT3DDEVICE9 pDevice);

	void VMTHook(void* Function, void* Hook);

	void Start();
	void Hook();

}; extern CHook* Hook;