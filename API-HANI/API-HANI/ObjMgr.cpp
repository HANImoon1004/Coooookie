#include "stdafx.h"
#include "ObjMgr.h"

#include "Obj.h"
#include "CollisionMgr.h"
#include "MapMgr.h"
#include "Player.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
	m_MapList[MAP_BLOCK] = CMapMgr::Get_Instance()->Get_Instance()->Get_MapList(MAP_BLOCK);
	m_MapList[MAP_OBSTACLE] = CMapMgr::Get_Instance()->Get_Instance()->Get_MapList(MAP_OBSTACLE);
}


CObjMgr::~CObjMgr()
{
	Release();
}

//CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
//{
//	if (m_ObjList[eID].empty())
//		return nullptr;
//
//
//	CObj*		pTarget = nullptr;
//	float		fDistance = 0.f;
//
//	for (auto& iter : m_ObjList[eID])
//	{
//		if (iter->Get_Dead())
//			continue;
//
//		float	fWidth = iter->Get_Info().fX - pObj->Get_Info().fX;
//		float	fHeight = iter->Get_Info().fY - pObj->Get_Info().fY;
//
//		float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
//
//		if (!pTarget || fDistance > fDiagonal)
//		{
//			pTarget = iter;
//			fDistance = fDiagonal;
//		}
//
//	}
//
//	return pTarget;
//}
//
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

	return 0;
}

void CObjMgr::Late_Update(void)
{
	/*for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID eID = iter->Get_GroupID();
			m_RenderSort[eID].push_back(iter);*/

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (int j = 0; j < m_ObjList[i].size(); ++j)
		{
			CObj* temp = m_ObjList[i].front() + j;
			if (temp == nullptr) continue;

			temp->Late_Update();
		}
	}

	CollisionMgr::Collision_Block(m_MapList[MAP_BLOCK], m_ObjList[OBJ_PLAYER]);
	if (CollisionMgr::Collision_Rect(m_MapList[MAP_BLOCK], m_ObjList[OBJ_PLAYER]))
	{
		dynamic_cast<Player*>(m_ObjList[OBJ_PLAYER].front())->Jump_Stop();
	}

//CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
//CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PLAYER]);
//CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
//CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
}

void CObjMgr::Render(HDC hDC)
{

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}

	for (int i = 0; i < RENDER_END; ++i) //0308 hani
	{
		m_RenderSort[i].sort(CompareY<CObj*>);

		for (auto& iter : m_RenderSort[i])
			iter->Render(hDC);

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
