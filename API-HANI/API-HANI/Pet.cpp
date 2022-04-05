#include "stdafx.h"
#include "Pet.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "MapMgr.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"
#include "Player.h"
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
	m_tFrame.iFrameEnd = 5;
	m_tFrame.dwSpeed = 300;
	m_pFrameKey = L"Gaeguri";
	m_eCurState = PET_IDLE;
	m_eNextState = PET_IDLE;
	m_bMagnet = false;
}

int CPet::Update(void)
{
	if (m_bMagnet)
	{
		m_eNextState = PET_MAGNET;
		float fX = 450 - m_tInfo.fX;
		float fY = 240 - m_tInfo.fY;
		float fDistance = sqrt(fX * fX + fY * fY);

		if (fX > 0)
		{
			m_tInfo.fX += 5 * fX / fDistance;
		}
		if (fY != 0)
		{
			m_tInfo.fY += 5 * fY / fDistance;
		}
	}

	else
	{
		float fX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX;
		float fY = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY;

		POINT pt;
		pt.x = fX - 130 - m_tInfo.fX;
		pt.y = fY - m_tInfo.fY;

		float Distance = sqrtf(pt.x * pt.x + pt.y * pt.y);

		/*if (Distance > 30)
		{
			m_tInfo.fX += 1;
			m_tInfo.fY += 1;
		}*/

		if (pt.x >= 50)
		{
			m_tInfo.fX += 3;
		}

		else if (pt.x * -1 >= 60)
			m_tInfo.fX -= 3;

		if (pt.y >= 20)
			m_tInfo.fY += 3;

		if (pt.y * -1 >= 30)
			m_tInfo.fY -= 3;
	}


	Update_Rect();
	Animation_Change();
	Move_Frame();
	return 0;
}

void CPet::Late_Update(void)
{
	if (m_dwTime + 3000 < GetTickCount())
	{
		CMapMgr::Get_Instance()->Set_Magnet(false);
		m_bMagnet = false;
		m_eNextState = PET_IDLE;
	}

	for (int i = 0; i < MAPID::MAP_END; i++)
	{
		list<CMaps*> temp = OBJMGR->Get_Map((MAPID)i);

		if ((MAPID)i == MAPID::MAP_BLOCK)
		{
			if (CollisionMgr::Collision_Block(temp, this))
			{
				switch ((MAPID)i)
				{
				case MAP_BLOCK:

					break;
				}
			}
		}
		else
		{
			for (auto& iter : temp)
			{
				if (CollisionMgr::Collision_Rect(iter, this))
				{
					int iMoney = iter->Get_Money();
					int iScore = iter->Get_Score() * 50;
					INMAP eID = iter->Get_INID();
					switch ((INMAP)eID)
					{
					case OBSTACLE: OTTE:

					break;
					case COIN_GB:
						iter->Set_Dead();
						CSoundMgr::Get_Instance()->PlaySound(L"Coin.wav", SOUND_EFFECT, CObj::g_fSound);
						CSoundMgr::Get_Instance()->PlaySound(L"KingCoin.wav", SOUND_COIN, CObj::g_fSound);
						break;
					case COIN_SB:
						iter->Set_Dead();
						CSoundMgr::Get_Instance()->PlaySound(L"Coin.wav", SOUND_EFFECT, CObj::g_fSound);
						CSoundMgr::Get_Instance()->PlaySound(L"KingCoin.wav", SOUND_COIN, CObj::g_fSound);
						break;
					case COIN_SS: 
						iter->Set_Dead();
						CSoundMgr::Get_Instance()->PlaySound(L"Coin.wav", SOUND_EFFECT, CObj::g_fSound);
						CSoundMgr::Get_Instance()->PlaySound(L"Coin.wav", SOUND_COIN, CObj::g_fSound);
						break;
					case COIN_GS:
						CSoundMgr::Get_Instance()->PlaySound(L"Coin.wav", SOUND_EFFECT, CObj::g_fSound);
						CSoundMgr::Get_Instance()->PlaySound(L"Coin.wav", SOUND_COIN, CObj::g_fSound);
						break;
					case JELLY:
						iter->Set_Dead();
						CSoundMgr::Get_Instance()->PlaySound(L"Jelly.wav", SOUND_JELLY, CObj::g_fSound);
						break;
					case BOOSTER:
					{
						dynamic_cast<Player*>(CObjMgr::Get_Instance()->Get_Player())->Set_Booster();
						iter->Set_Dead();
						CSoundMgr::Get_Instance()->PlaySound(L"아이템.wav", SOUND_EFFECT, CObj::g_fSound);
						float fX = temp.front()->Get_MapInfo()->tPoint.fX;
						float fY = temp.front()->Get_MapInfo()->tPoint.fY;
					}
					break;
					case BIG:
						CSoundMgr::Get_Instance()->PlaySound(L"아이템.wav", SOUND_EFFECT, CObj::g_fSound);
						dynamic_cast<Player*>(CObjMgr::Get_Instance()->Get_Player())->Set_Big();
						iter->Set_Dead();
					case MAGNET:
						Set_Magnet();
						//dynamic_cast<CPet*>(CObjMgr::Get_Instance()->Get_Obj(OBJ_PET).front())->Set_Magnet();
						CMapMgr::Get_Instance()->Set_Magnet(true);
						iter->Set_Dead();
						break;
					default:
						break;
					}
				}
			}

		}
	}
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

void CPet::Animation_Change()
{
	if (m_eCurState != m_eNextState) {
		switch (m_eNextState) {
		case PET_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameAnimation = 0;
			m_tFrame.dwSpeed = 300;
			break;
		case PET_MAGNET:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameAnimation = 1;
			m_tFrame.dwSpeed = 200;
			break;
		default:
			break;
		}
		m_eCurState = m_eNextState;
	}
}

void CPet::Set_Magnet()
{
	m_dwTime = GetTickCount();
	m_eNextState = PET_MAGNET;
	m_bMagnet = true;
}
