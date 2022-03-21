#include "stdafx.h"
#include "MapMgr.h"
#include "KeyMgr.h"
#include "Obstacle.h"
#include "Coin.h"
#include "BCoin.h"
#include "GCoin.h"
#include "BGCoin.h"
#include "Jelly.h"
#include "Booster.h"
#include "Big.h"
#include "Magnet.h"
#include "Otte.h"
#include "MidBlock.h"

CMapMgr* CMapMgr::m_pInstance = nullptr;

CMapMgr::CMapMgr()
{
	Load_Map();
}


CMapMgr::~CMapMgr()
{
	Release();
}

void CMapMgr::Initialize()
{
}

void CMapMgr::Update()
{
	/*if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		Load_Map();
	}*/

	for (int i = 0; i < MAP_END; ++i)
	{
		/*for (int j = 0; j < sizeof(m_listMap[i]); ++j)
		{
			m_listMap[i].()->Update();
		}*/
		auto& iter = m_listMap[i].begin();

		for (; iter != m_listMap[i].end();) //0316 QUE hani 
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CMaps*>(*iter);
				iter = m_listMap[i].erase(iter);
			}

			else
				++iter;
		}

	}
}

void CMapMgr::Late_Update(HDC hDC)
{
	for (int i = 0; i < MAP_END; ++i)
	{
		auto& iter = m_listMap[i].begin();

		for (; iter != m_listMap[i].end();) //0316 QUE hani 
		{
			int iEvent = (*iter)->Late_Update(hDC);

			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CMaps*>(*iter);
				iter = m_listMap[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CMapMgr::Render(HDC hDC)
{
	for (int i = 0; i < MAP_END; ++i)
	{
		for (auto& iter : m_listMap[i])
		{
			iter->Render(hDC);
		}
	}
}

void CMapMgr::Release()
{
	for (int i = 0; i < MAP_END; ++i)
	{
		for_each(m_listMap[i].begin(), m_listMap[i].end(), Safe_Delete<CMaps*>);
	}
}

void CMapMgr::Load_Map()
{
	HANDLE hFile = CreateFile(__T("../Data/Map.dat"),
		GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(nullptr, __T("로드 실패ㅠ_ㅠ"), __T("맵"), MB_OK);
		return;
	}
	CMaps* pMap = nullptr;
	DWORD dwByte = 0;
	MAPINFO tMapInfo = {};
	INMAP eINID;

	while (true)
	{
		ReadFile(hFile, &tMapInfo, sizeof(MAPINFO), &dwByte, nullptr);
		ReadFile(hFile, &eINID, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;
		switch (eINID)
		{
		case BLOCK:
			pMap = new CBlock(tMapInfo, eINID);
			m_listMap[MAP_BLOCK].push_back(pMap);
			break;

		case MIDBLOCK:
			pMap = new MidBlock(tMapInfo, eINID);
			m_listMap[MAP_BLOCK].push_back(pMap);
			break;

		case OBSTACLE:
			pMap = new Obstacle(tMapInfo, eINID);
			m_listMap[MAP_OBSTACLE].push_back(pMap);
			break;

		case OTTE:
			pMap = new Otte(tMapInfo, eINID);
			m_listMap[MAP_OBSTACLE].push_back(pMap);
			break;

		case COIN_SS:
			pMap = new Coin(tMapInfo, eINID);
			m_listMap[MAP_COIN].push_back(pMap);
			break;

		case COIN_SB:
			pMap = new BCoin(tMapInfo, eINID);
			m_listMap[MAP_COIN].push_back(pMap);
			break;

		case  COIN_GS:
			pMap = new CGCoin(tMapInfo, eINID);
			m_listMap[MAP_COIN].push_back(pMap);
			break;

		case COIN_GB:
			pMap = new BGCoin(tMapInfo, eINID);
			m_listMap[MAP_COIN].push_back(pMap);
			break;

		case JELLY:
			pMap = new Jelly(tMapInfo, eINID);
			m_listMap[MAP_JELLY].push_back(pMap);
			break;

		case BOOSTER:
			pMap = new Booster(tMapInfo, eINID);
			m_listMap[MAP_ITEM].push_back(pMap);
			break;

		case  BIG:
			pMap = new Big(tMapInfo, eINID);
			m_listMap[MAP_ITEM].push_back(pMap);
			break;

		case MAGNET:
			pMap = new Magnet(tMapInfo, eINID);
			m_listMap[MAP_ITEM].push_back(pMap);
			break;
		}
	}

//	MessageBox(nullptr, L">>ㅑ 로드 성공!", L"*-클라이언트-*", MB_OK);
	CloseHandle(hFile);
}
