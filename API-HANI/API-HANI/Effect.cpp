#include "stdafx.h"
#include "Effect.h"
#include "MapMgr.h"

CEffect::CEffect()
{
}


CEffect::~CEffect()
{
}

CEffect::CEffect(float fX, float fY, float fCX, float fCY, EFFECT eID, TCHAR* pFrameKey)
	: m_fX(fX), m_fY(fY), m_fCX(fCX), m_fCY(fCY), m_eID(eID), m_pFrameKey(pFrameKey)
{
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));
}

void CEffect::Initialize(void)
{
}

int CEffect::Update(void)
{

	Move_Frame();
	return OBJ_NOEVENT;
}


void CEffect::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC, m_tInfo.fX - m_tInfo.fCX / 2.f + iScrollX,
		m_tInfo.fY - m_tInfo.fCY / 2.f,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * m_tInfo.fCX,
		m_tFrame.iFrameAnimation * m_tInfo.fCY,
		m_tInfo.fCX,
		m_tInfo.fCY,
		ASHBLUE);



}
void CEffect::Release(void)
{
}
