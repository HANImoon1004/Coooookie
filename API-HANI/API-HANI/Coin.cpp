#include "stdafx.h"
#include "Coin.h"
#include "EffectMgr.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"
#include "AbstractFactory.h"

Coin::Coin()
{
	m_tInfo = MAPINFO(SCOINS_CX, SCOINS_CY);
	m_eINID = COIN_SS;
	m_iMoney = 50;
	m_iScore = 30;
}

Coin::Coin(MAPINFO & mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
	m_bDead = false;
	/*m_tRect.left = m_tInfo.tPoint.fX - m_tInfo.tPoint.iCX * 0.5;
	m_tRect.right = m_tInfo.tPoint.fX + m_tInfo.tPoint.iCX * 0.5;
	m_tRect.top = m_tInfo.tPoint.fY - m_tInfo.tPoint.iCY * 0.5;
	m_tRect.bottom = m_tInfo.tPoint.fY + m_tInfo.tPoint.iCY * 0.5;
*/
	m_iMoney = 50;
	m_iScore = 30;
	m_tFrame.iFrameStart = 0;//가로 시작
	m_tFrame.iFrameEnd = 3; //가로 끝
	m_tFrame.iFrameAnimation = 0;//세로 시작 위치
	m_tFrame.dwSpeed = 100; //낮을 수록 빠름
}


Coin::~Coin()
{
}

void Coin::Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

void Coin::Animation_Change()
{
}

int Coin::Update()
{
	m_tInfos.fCX = 68.f;
	m_tInfos.fCY = 68.f;
	m_tInfos.fX = m_tInfo.tPoint.fX;
	m_tInfos.fY = m_tInfo.tPoint.fY;

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void Coin::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SilverCoin");

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	GdiTransparentBlt(hDC, m_tInfo.tPoint.fX - m_tInfo.tPoint.iCX / 2.f + iScrollX, //Q
		m_tInfo.tPoint.fY - m_tInfo.tPoint.iCY / 2.f,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		hMemDC,
		m_tFrame.iFrameStart*m_tInfo.tPoint.iCX,
		m_tFrame.iFrameAnimation*m_tInfo.tPoint.iCY,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		ASHBLUE);
}

int Coin::Late_Update(HDC hDC)
{
	//m_tInfos.fCX = 68.f;
	//m_tInfos.fCY = 68.f;
	//m_tInfos.fX = m_tInfo.tPoint.fX;
	//m_tInfos.fY = m_tInfo.tPoint.fY;
	
	CObj* player = OBJMGR->Get_Player();
	if (player == nullptr) return OBJ_NOEVENT;

	if (CollisionMgr::Collision_Rect(this, player))
	{
		m_bDead = true;
		CSoundMgr::Get_Instance()->PlaySound(L"Coin.wav", SOUND_EFFECT, CObj::g_fSound);
		CSoundMgr::Get_Instance()->PlaySound(L"Coin.wav", SOUND_COIN, CObj::g_fSound);
		//CEffect* effect = new CEffect(m_tInfos.fX, m_tInfos.fY,
			//m_tInfos.fCX, m_tInfos.fCY, EF_COIN, L"Coin_Effect");
		//CObj* pObj = CAbstractFactory<CEffect>::Create();
		CObj* pObj = new CEffect(m_tInfos.fX, m_tInfos.fY,
			m_tInfos.fCX, m_tInfos.fCY, EF_COIN, L"Coin_Effect");
		CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, pObj);
		
		
	}

	if (true == m_bDead)
	{
	


		return OBJ_DEAD;
	}
	else
		return OBJ_NOEVENT;
}
