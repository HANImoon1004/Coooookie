#include "stdafx.h"
#include "Obj.h"
#include "ObjMgr.h"

float CObj::g_fSound = 0.5f;

CObj::CObj()
	: m_fSpeed(0.f), m_bDead(false), m_fAngle(0.f), m_fDiagonal(0.f)
	, m_eGroup(RENDERID(RENDER_END))
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	//ZeroMemory(&m_tDraw, sizeof(DRAW));
	ZeroMemory(&m_tRect, sizeof(RECT));
	//ZeroMemory(&m_tFrame, sizeof(FRAME));

}


CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Move_Frame(void)
{
	if (m_tFrame.dwSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}
