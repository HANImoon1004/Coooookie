#include "stdafx.h"
#include "Mouse.h"
#include "CScrollMgr.h"	
CMouse* CMouse::m_pInstance = nullptr;

CMouse::CMouse()
{

	m_tInfo.fX = 0;
	m_tInfo.fY = 0;
	m_tInfo.fCX = 5.f;
	m_tInfo.fCY = 5.f;

}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	m_tInfo.fX = pt.x-iScrollX;
	m_tInfo.fY = pt.y;

	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CMouse::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse::Release()
{
	if (m_pInstance)
	{
		Safe_Delete(m_pInstance);
	}
}
