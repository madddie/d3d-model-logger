#include "Include.h"

class CSDK
{
public:
	int StrideCoefficient = 1, NumVerticesCoefficient = 1, PrimCountCoefficient = 1;

	void Frame(LPDIRECT3DDEVICE9 pDevice);

}; extern CSDK* SDK;