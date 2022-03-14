#include "stdafx.h"
#include "Stage01.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "CScrollMgr.h"
#include "AbstractFactory.h"
#include "Soup.h"
#include "Player.h"

//#define MAX_COMPUTERNAME_LENGTH 31

CStage01::CStage01()
{
}


CStage01::~CStage01()
{
}

void CStage01::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map1.bmp", L"Map1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Run.bmp", L"Player_Run"); //�÷��̾�


	CObj* pObj = nullptr;
	
	pObj = CAbstractFactory<Player>::Create();
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, pObj);

	
}

int CStage01::Update(void)
{
	if (GetAsyncKeyState(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (GetAsyncKeyState(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	if (GetAsyncKeyState(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(5.f);

	if (GetAsyncKeyState(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	}

	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CStage01::Late_Update(void)
{
	//CObjMgr::Get_Instance()->Late_Update(); //���ݶ�
}

void CStage01::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Map1");//�޴� ���

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC,
		iScrollX,
		iScrollY,
		1063, //�̹��� ������ x
		1131, //�̹��� ������ y
		hMemDC,
		0,
		0,
		SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);

	AddFontResourceA("../Font/PF��Ÿ����Ʈ.ttf");

	SetBkMode(hDC, 1);
	SetTextColor(hDC, RGB(255, 255, 255));
	HFONT hFont, oldFont;
	hFont = CreateFont(20, //����
		0, 0, 0, 0, 0, 0, 0, 
		HANGUL_CHARSET, 0, 0, 0, 
		VARIABLE_PITCH || FF_ROMAN, 
		TEXT("PF��Ÿ����Ʈ")); //��Ʈ

	oldFont = (HFONT)SelectObject(hDC, hFont);
	TextOut(hDC, 300, 600, L"�ȳ�!", lstrlen(L"�ȳ�"));

	TextOut(hDC, 300, 300, L"�ȳ�", lstrlen(L"�ȳ�"));

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
	TextOut(hDC, 300, 400, szComName, lstrlen(szComName)); //�����ϴ� �ȳ�!
	TextOut(hDC, 300, 500, L"1. ���ϱ�  2. ���ϱ�", lstrlen(L"1. ���ϱ�  2. ���ϱ�"));


}

void CStage01::Release(void)
{
}
