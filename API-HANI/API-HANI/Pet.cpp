#include "stdafx.h"
#include "Pet.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

CPet::CPet()
{
}

CPet::~CPet()
{
	Release();
}

void CPet::Initialize(void)
{
	m_tInfo.fX = 50.f;
	m_tInfo.fY = 100.f; 
	m_tInfo.fCX = PET_CX;
	m_tInfo.fCY = PET_CY;
	m_tFrame.iFrameAnimation = 0;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.dwSpeed = 100;
	m_pFrameKey = L"Gaeguri";
}

int CPet::Update(void)
{
	float fX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX;
	float fY = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY;

	POINT pt;
	pt.x =  fX - 30 - m_tInfo.fX;
	pt.y = fY - m_tInfo.fY;

	float Distance = sqrtf(pt.x * pt.x + pt.y * pt.y);

	/*if (Distance > 30)
	{
		m_tInfo.fX += 1;
		m_tInfo.fY += 1;
	}*/

	if (pt.x >= 50)
	{
		m_tInfo.fX += 1;
	}

	else if (pt.x * -1 >= 50)
		m_tInfo.fX -= 1;

	if (pt.y >= 30)
		m_tInfo.fY += 1;

	if (pt.y * -1 >= 30)
		m_tInfo.fY -= 1;

	Update_Rect();
	return 0;
}

void CPet::Late_Update(void)
{
}

void CPet::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);



		GdiTransparentBlt(hDC,
			m_tInfo.fX - 80,//복사 받을 위치 좌표
			m_tInfo.fY - 80,
			(int)m_tInfo.fCX, //복사 받을 가로 길이
			(int)m_tInfo.fCY,
			hMemDC,
			int(m_tInfo.fCX) * m_tFrame.iFrameStart, //비트맵의 시작 좌표값 출력 시작 지점
			int(m_tInfo.fCY) * m_tFrame.iFrameAnimation, //비트맵의 시작 좌표값 출력 시작 지점,
			int(m_tInfo.fCX), //복사 할 비트맵 가로 길이
			int(m_tInfo.fCY),
			ASHBLUE);
}

void CPet::Release(void)
{
}
