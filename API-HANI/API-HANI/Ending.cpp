#include "stdafx.h"
#include "Ending.h"
#include "BmpMgr.h"
#include "Player.h"

Ending::Ending()
{
}

Ending::~Ending()
{
	Release();
}

void Ending::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ending.bmp", L"Ending");

}

int Ending::Update(void)
{
	return 0;
}

void Ending::Late_Update(void)
{
}

void Ending::Render(HDC hDC)
{
	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Ending");

	BitBlt(hDC,			
		0, 
		0,
		WINCX,	
		WINCY,
		hBackDC,			
		0,				
		0,
		SRCCOPY);

	int iMoney = dynamic_cast<Player*>(CObjMgr::Get_Instance()->Get_Player())->Get_Money();
	int iScore = dynamic_cast<Player*>(CObjMgr::Get_Instance()->Get_Player())->Get_Score();

	TCHAR szMoney[32];
	TCHAR szScore[32];
	TCHAR szHp[32];
	SetBkMode(hDC, 1);
	SetTextColor(hDC, WHITE);
	HFONT hFont, oldFont;
	hFont = CreateFont(50, //높이
		0, 0, 0, 0, 0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH || FF_ROMAN,
		TEXT("CookieRun Black")); //폰트
	oldFont = (HFONT)SelectObject(hDC, hFont);

	wsprintf(szScore, L"%i 점!", iScore); 
	TextOut(hDC, 370, 300, szScore, lstrlen(szScore));

	wsprintf(szMoney, L"%i 원", iMoney);
	TextOut(hDC, 330, 380, szMoney, lstrlen(szMoney));
}

void Ending::Release(void)
{
}
