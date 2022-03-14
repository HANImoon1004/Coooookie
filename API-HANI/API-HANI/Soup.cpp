#include "stdafx.h"
#include "Soup.h"
#include "BmpMgr.h"
#include "CScrollMgr.h"

Soup::Soup()
	: m_iDrawID(0), m_iDrawID2(0)
{
}

Soup::~Soup()
{
	Release();
}

void Soup::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Nya/bongji.bmp", L"Bongji");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Nya/Snow_bongji.bmp", L"Snow_Bongji");

	m_tInfo.fCX = 163.f;
	m_tInfo.fCY = 134.f;
}

int Soup::Update(void)
{
	
	
	Update_Rect();
	return 0;
}

void Soup::Late_Update(void)
{


}

void Soup::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Bongji");

	dwOldTime = GetTickCount();

	if (dwOldTime + 10 < GetTickCount())
	{
		m_iDrawID = 1;
	}
	GdiTransparentBlt(hDC,
		m_tRect.left+iScrollX,
		m_tRect.top+iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		(int)m_tInfo.fCX * m_iDrawID,
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(168, 168, 168));

	//switch (BONGJI)
	//{
	//case BONGJI_IDLE:
	//	
	//	break;
	//case BONGJI_SNOW:
	//	break;
	//case BONGJI_END:
	//	break;
	//default:
	//	break;
	//}
}

void Soup::Release(void)
{
}
