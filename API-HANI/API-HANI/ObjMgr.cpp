#include "stdafx.h"
#include "ObjMgr.h"

#include "Obj.h"
#include "CollisionMgr.h"
#include "MapMgr.h"
#include "Player.h"

#include "Coin.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "EffectMgr.h"
#include "Effect.h"
#include "Coin.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{

		m_MapList[MAP_BLOCK] = CMapMgr::Get_Instance()->Get_Instance()->Get_MapList(MAP_BLOCK);
		m_MapList[MAP_OBSTACLE] = CMapMgr::Get_Instance()->Get_Instance()->Get_MapList(MAP_OBSTACLE);
		m_MapList[MAP_COIN] = CMapMgr::Get_Instance()->Get_Instance()->Get_MapList(MAP_COIN);
		m_MapList[MAP_JELLY] = CMapMgr::Get_Instance()->Get_Instance()->Get_MapList(MAP_JELLY);
		m_MapList[MAP_ITEM] = CMapMgr::Get_Instance()->Get_Instance()->Get_MapList(MAP_ITEM);

	

	
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::AddObject(OBJID eID, CObj* pObj)
{
	if (eID >= OBJ_END || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		auto& iter = m_ObjList[i].begin();

		for (; iter != m_ObjList[i].end(); )
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	//if (dynamic_cast<Player*>(CObjMgr::Get_Instance()->Get_Player()))
	//{
	//	//죽었으면... 팝업창
	//}

	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (int j = 0; j < m_ObjList[i].size(); ++j)
		{
			CObj* temp = m_ObjList[i].front() + j;
			if (temp == nullptr) continue;

			temp->Late_Update();
		}
	}
	//충돌처리
	
	//CollisionMgr::Collision_Block(m_MapList[MAP_BLOCK], m_ObjList[OBJ_PLAYER]);
	//if (CollisionMgr::Collision_Rect(m_MapList[MAP_BLOCK], m_ObjList[OBJ_PLAYER]))
	//{
 	//	dynamic_cast<Player*>(m_ObjList[OBJ_PLAYER].front())->Jump_Stop();
	//}
	//CollisionMgr::Collision_Otte(m_MapList[MAP_OBSTACLE], m_ObjList[OBJ_PLAYER]);
	//
	////if(CollisionMgr::Collision_Map(m_MapList[MAP_COIN], m_ObjList[OBJ_PLAYER]))
	////{
	//
	////	m_MapList[MAP_COIN].front()->Set_Dead(); //0317
	//
	////
	////}//collision_block jal daem.  이러면 맨 앞의 하나만 사라진다.
	//
	//if (CollisionMgr::Collision_Item(m_MapList[MAP_COIN], m_ObjList[OBJ_PLAYER]))
	//{
	//	CSoundMgr::Get_Instance()->PlaySound(L"Coin.wav", SOUND_EFFECT, CObj::g_fSound);
	//	CSoundMgr::Get_Instance()->PlaySound(L"Coin.wav", SOUND_COIN, CObj::g_fSound);
	//	CSoundMgr::Get_Instance()->PlaySound(L"KingCoin.wav", SOUND_COIN, CObj::g_fSound);
	//	float fX = m_MapList[MAP_COIN].front()->Get_MapInfo()->tPoint.fX;
	//	float fY = m_MapList[MAP_COIN].front()->Get_MapInfo()->tPoint.fY;
	///*	CObj* pObj = new CEffect(fX, fY, 68, 68, EF_COIN, L"Coin_Effect");
	//	m_ObjList[OBJ_EFFECT].push_back(pObj);*/
	//
	//}
	//
	//
	//
	//CollisionMgr::Collision_Item(m_MapList[MAP_OBSTACLE], m_ObjList[OBJ_PLAYER]);
	//CollisionMgr::Collision_Item(m_MapList[MAP_ITEM], m_ObjList[OBJ_PLAYER]);
	//if (CollisionMgr::Collision_Item(m_MapList[MAP_JELLY], m_ObjList[OBJ_PLAYER]))
	//{
	//	CSoundMgr::Get_Instance()->PlaySound(L"Jelly.wav", SOUND_JELLY, CObj::g_fSound);
	//
	//}

}

void CObjMgr::Render(HDC hDC)
{

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			if (iter == nullptr)
				return;

			iter->Render(hDC);

		}
	}

	for (int i = 0; i < RENDER_END; ++i) //0308 hani
	{
		m_RenderSort[i].sort(CompareY<CObj*>);

		for (auto& iter : m_RenderSort[i])
		{
			iter->Render(hDC);
		}
			
		m_RenderSort[i].clear();			// 매 프레임마다 정렬 상태가 달라지기 때문
	}
}

void CObjMgr::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		//for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj());
		m_ObjList[i].clear();
	}

	for (int i = 0; i < RENDER_END; ++i)
		m_RenderSort[i].clear();

}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}
