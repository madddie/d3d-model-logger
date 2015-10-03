#include "SDK.h"
#include "Render.h"
#include "Tools.h"

void CSDK::Frame(LPDIRECT3DDEVICE9 pDevice)
{
	if (GETKEY(VK_NUMPAD8))
		StrideCoefficient++;

	if (GETKEY(VK_NUMPAD2))
		StrideCoefficient--;

	if (GETKEY(VK_NUMPAD7))
		NumVerticesCoefficient++;

	if (GETKEY(VK_NUMPAD1))
		NumVerticesCoefficient--;

	if (GETKEY(VK_NUMPAD9))
		PrimCountCoefficient++;

	if (GETKEY(VK_NUMPAD3))
		PrimCountCoefficient--;

	if (GETKEY(VK_F5))
		Tools->WriteLog("(NumVertices == %d && PrimitiveCount == %d && Stride == %d)\n", NumVerticesCoefficient, PrimCountCoefficient, StrideCoefficient);

	Render->DrawFText(10, 10, LAWNGREEN(255), 1, 0, Render->Font, pDevice, "[ Maddy Model Logger ]\n[ Stride: %d ]\n[ Verts: %d ]\n[ Prims: %d ]\n[ F5 Log ]", StrideCoefficient, NumVerticesCoefficient, PrimCountCoefficient);
}