#include "stdafx.h"
#include "MyMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "SoundMgr.h"
#include "MenuPlayer.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Button.bmp", L"Button");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Pancake.bmp", L"Pancake"); //플레이어
	CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/Night_Sea_Under_The_Moonlight.mp3",SOUND_BGM, CObj::g_fSound);
	//CObj* pObj = CAbstractFactory<CMyButton>::Create(330.f, 242.f);
	//pObj->Set_FrameKey(L"Button");
	//CObjMgr::Get_Instance()->AddObject(OBJ_UI, pObj);

	CObj* pObj = CAbstractFactory<MenuPlayer>::Create(207.f, 220.f);
	pObj->Set_FrameKey(L"Pancake");
	CObjMgr::Get_Instance()->AddObject(OBJ_UI, pObj);
}

int CMyMenu::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"Night_Sea_Under_The_Moonlight.mp3", SOUND_BGM,CObj::g_fSound);
	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CMyMenu::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

}

void CMyMenu::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");//메뉴 배경

	BitBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		hMemDC,
		0,
		0,
		SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);

	AddFontResourceA("../Font/PF스타더스트.ttf");

	SetBkMode(hDC, 1);
	SetTextColor(hDC, RGB(122, 146, 190));
	HFONT hFont, oldFont;
	hFont = CreateFont(20, //높이
		0, 0, 0, 0, 0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH || FF_ROMAN,
		TEXT("PF스타더스트")); //폰트
	oldFont = (HFONT)SelectObject(hDC, hFont);
	TCHAR szComName[255]; //hani 컴퓨터, 유저 이름
	TCHAR szUserName[255];
	TCHAR str[255];
	DWORD len;
	HDC hdc;
	PAINTSTRUCT ps;
	hdc = BeginPaint(g_hWnd, &ps);
	len = 255;
	GetComputerName(szComName, &len);
	len = 255;
	GetUserName(szUserName, &len);

	TextOut(hDC, 300, 300, szComName, lstrlen(szComName)); //단순히 지영하니 뜸
	wsprintf(szComName, L"%s 안녕!", szComName); //세번째 인수는 %s, 2인자를 1인자에 복사해주는 것 같다
	TextOut(hDC, 400, 100, szComName, lstrlen(szComName)); //지영하니 안녕!

	wsprintf(szUserName, L"%s 안녕!", szUserName); //세번째 인수는 %s, 2인자를 1인자에 복사해주는 것 같다
	TextOut(hDC, 400, 450, szUserName, lstrlen(szUserName)); //지영하니 안녕!

	TextOut(hDC, 300, 500, L"1. 일하기  2. 일하기", lstrlen(L"1. 일하기  2. 일하기"));


}

void CMyMenu::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_UI);

}
