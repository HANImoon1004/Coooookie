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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Pancake.bmp", L"Pancake"); //�÷��̾�
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
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Menu");//�޴� ���

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

	AddFontResourceA("../Font/PF��Ÿ����Ʈ.ttf");

	SetBkMode(hDC, 1);
	SetTextColor(hDC, RGB(122, 146, 190));
	HFONT hFont, oldFont;
	hFont = CreateFont(20, //����
		0, 0, 0, 0, 0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH || FF_ROMAN,
		TEXT("PF��Ÿ����Ʈ")); //��Ʈ
	oldFont = (HFONT)SelectObject(hDC, hFont);
	TCHAR szComName[255]; //hani ��ǻ��, ���� �̸�
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

	TextOut(hDC, 300, 300, szComName, lstrlen(szComName)); //�ܼ��� �����ϴ� ��
	wsprintf(szComName, L"%s �ȳ�!", szComName); //����° �μ��� %s, 2���ڸ� 1���ڿ� �������ִ� �� ����
	TextOut(hDC, 400, 100, szComName, lstrlen(szComName)); //�����ϴ� �ȳ�!

	wsprintf(szUserName, L"%s �ȳ�!", szUserName); //����° �μ��� %s, 2���ڸ� 1���ڿ� �������ִ� �� ����
	TextOut(hDC, 400, 450, szUserName, lstrlen(szUserName)); //�����ϴ� �ȳ�!

	TextOut(hDC, 300, 500, L"1. ���ϱ�  2. ���ϱ�", lstrlen(L"1. ���ϱ�  2. ���ϱ�"));


}

void CMyMenu::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_UI);

}
