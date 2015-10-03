#include "Render.h"

int CRender::GetTextLength(const char* szText, LPD3DXFONT pFont)
{
	RECT Rect = { 0, 0, 0, 0 };

	pFont->DrawTextA(0, szText, -1, &Rect, DT_CALCRECT, 0x0);

	return Rect.right - Rect.left;
}

void CRender::DrawRectSolid(int x, int y, int w, int h, DWORD color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DRECT BarRect = { x, y, x + w, y + h };
	//We clear that portion of the screen and display our rectangle
	pDevice->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
}

void CRender::DrawFText(int x, int y, DWORD color, bool shadow, bool center, LPD3DXFONT pFont, LPDIRECT3DDEVICE9 pDevice, const char* szText, ...)
{
	bool FoundNewline = false;
	int HeightMultiplier = 0;

	for (int i = 0; size_t(i) < strlen(szText); ++i)
	{
		if (szText[i] == '\n')
		{
			++HeightMultiplier;
			FoundNewline = true;
		}
	}
	if (!FoundNewline)
		HeightMultiplier = 1;

	RECT FontPos = { x, y, x + 50, y + 50 };

	RECT ShadowPos[7];

	ShadowPos[0] = { x - 1, y - 1, x + 50, y + 50 };
	ShadowPos[1] = { x, y - 1, x + 50, y + 50 };
	ShadowPos[2] = { x + 1, y - 1, x + 50, y + 50 };
	ShadowPos[3] = { x - 1, y, x + 50, y + 50 };
	ShadowPos[4] = { x + 1, y, x + 50, y + 50 };
	ShadowPos[5] = { x - 1, y + 1, x + 50, y + 50 };
	ShadowPos[6] = { x, y + 1, x + 50, y + 50 };

	char buf[1024] = { '\0' };
	va_list va_alist;

	va_start(va_alist, szText);
	vsprintf_s(buf, szText, va_alist);
	va_end(va_alist);

	if (center)
	{
		int Width = GetTextLength(buf, pFont);;
		if (center)
		{
			FontPos.left -= Width / 2;

			for (int i = 0; i < 7; ++i)
				ShadowPos[i].left -= Width / 2;
		}
	}

	if (shadow)
	{
		pFont->DrawTextA(NULL, buf, -1, &ShadowPos[0], DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
		pFont->DrawTextA(NULL, buf, -1, &ShadowPos[1], DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
		pFont->DrawTextA(NULL, buf, -1, &ShadowPos[2], DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
		pFont->DrawTextA(NULL, buf, -1, &ShadowPos[3], DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
		pFont->DrawTextA(NULL, buf, -1, &ShadowPos[4], DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
		pFont->DrawTextA(NULL, buf, -1, &ShadowPos[5], DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
		pFont->DrawTextA(NULL, buf, -1, &ShadowPos[6], DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
	}

	pFont->DrawTextA(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}