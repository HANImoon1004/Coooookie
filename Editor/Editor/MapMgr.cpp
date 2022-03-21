#include "stdafx.h"
#include "MapMgr.h"
#include "Maps.h"
#include "KeyMgr.h"
#include "CScrollMgr.h"
#include "Block.h"
#include "Obstacle.h"
#include "Coin.h"
#include "GCoins.h"
#include "Otte.h"
#include "Jelly.h"
#include "BigSVcoin.h"
#include "BigGDcoin.h"
#include "GCoins.h"
#include "Booster.h"
#include "Big.h"
#include "Magnet.h"
#include "CollisionMgr.h"
#include "Mouse.h"
#include "MidairBlock.h"

CMapMgr* CMapMgr::m_pInstance = nullptr;

CMapMgr::CMapMgr()
{
	m_tFrameKey = NULL;
}


CMapMgr::~CMapMgr()
{
	Release();
}

void CMapMgr::Save_Map()
{
	HANDLE hFile = CreateFile(__T("../Data/Map.dat"),
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(nullptr, __T("저장 실패ㅠ_ㅠ"), __T("맵"), MB_OK);
		return;
	}
	DWORD dwByte = 0;

	for (int i = 0; i < MAP_END; ++i)
	{
		for (auto& iter : m_listMap[i])
		{
			WriteFile(hFile, iter->Get_MapInfo(), sizeof(MAPINFO), &dwByte, nullptr);
			WriteFile(hFile, iter->Get_INID(), sizeof(int), &dwByte, nullptr); //요기 Q
		}
	}

	MessageBox(nullptr, L"맵 저장 성공!", L"*-맵-*", MB_OK);
	CloseHandle(hFile);
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
			pMap = new MidairBlock(tMapInfo, eINID);
			m_listMap[MAP_BLOCK].push_back(pMap);
			break;

		case OBSTACLE:
			pMap = new CObstacle(tMapInfo, eINID);
			m_listMap[MAP_OBSTACLE].push_back(pMap);
			break;

		case OTTE:
			pMap = new COtte(tMapInfo, eINID);
			m_listMap[MAP_OBSTACLE].push_back(pMap);
			break;

		case COIN_SS:
			pMap = new CCoin(tMapInfo, eINID);
			m_listMap[MAP_COIN].push_back(pMap);
			break;

		case COIN_GS:
			pMap = new CGCoins(tMapInfo, eINID);
			m_listMap[MAP_COIN].push_back(pMap);
			break;
		case COIN_SB:
			pMap = new BigSVcoin(tMapInfo, eINID);
			m_listMap[MAP_COIN].push_back(pMap);
			break;

		case COIN_GB:
			pMap = new BigGDcoin(tMapInfo, eINID);
			m_listMap[MAP_COIN].push_back(pMap);
			break;

		case JELLY:
			pMap = new CJelly(tMapInfo, eINID);
			m_listMap[MAP_JELLY].push_back(pMap);
			break;

		case BOOSTER:
			pMap = new Booster(tMapInfo, eINID);
			m_listMap[MAP_ITEM].push_back(pMap);
			break;

		case BIG:
			pMap = new Big(tMapInfo, eINID);
			m_listMap[MAP_ITEM].push_back(pMap);
			break;

		case MAGNET:
			pMap = new Magnet(tMapInfo, eINID);
			m_listMap[MAP_ITEM].push_back(pMap);
			break;
		}
	}

	MessageBox(nullptr, L">>ㅑ 로드 성공!", L"*-맵 에디터-*", MB_OK);
	CloseHandle(hFile);
}

void CMapMgr::Initialize()
{
}

void CMapMgr::Update()
{
	for (int i = 0; i < MAP_END; ++i)
	{
		auto& iter = m_listMap[i].begin();
		
		for (; iter != m_listMap[i].end();)
		{
			int iEvent = (*iter)->Update();

			if (MAP_DEAD == iEvent)
			{
				Safe_Delete<CMaps*>(*iter);
				iter = m_listMap[i].erase(iter);
			}
			else
				++iter;
		}
	}
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= CScrollMgr::Get_Instance()->Get_ScrollY();

	
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-10);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(+10);

	if (CKeyMgr::Get_Instance()->Key_Down('B'))//블럭
	{
		m_eID = MAP_BLOCK;
		m_iMapKey = 1;
		m_tFrameKey = L"Block";
		m_iMCX = BLOCK_CX;
		m_iMCY = BLOCK_CY;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('C'))//고양이
	{
		m_eID = MAP_OBSTACLE;
		m_iMapKey = 1;
		m_tFrameKey = L"Cat";
		m_iMCX = CAT_CX;
		m_iMCY = CAT_CY;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('D'))//실버 코인
	{
		m_eID = MAP_COIN;
		m_iMapKey = 1;
		m_tFrameKey = L"SilverCoin";
		m_iMCX = SCOINS_CX;
		m_iMCY = SCOINS_CY;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('J'))//강쥐 젤리
	{
		m_eID = MAP_JELLY;
		m_iMapKey = 1;
		m_tFrameKey = L"Jelly";
		m_iMCX = JELLY_CX;
		m_iMCY = JELLY_CY;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('I'))//부스터
	{
		m_eID = MAP_ITEM;
		m_iMapKey = 1;
		m_tFrameKey = L"Booster";
		m_iMCX = BOOSTER_CX;
		m_iMCY = BOOSTER_CY;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		m_iMapKey = 1;
		if (m_eID == MAP_BLOCK)
		{
			m_eID = MAP_BLOCK;
			m_iMapKey = 1;
			m_tFrameKey = L"Block";
			m_iMCX = BLOCK_CX;
			m_iMCY = BLOCK_CY;
		}
		if (m_eID == MAP_OBSTACLE)
		{
			m_eID = MAP_OBSTACLE;
			m_tFrameKey = L"Otte";
			m_iMCX = OTTE_CX;
			m_iMCY = OTTE_CY;
		}

		if (m_eID == MAP_COIN)
		{
			m_eID = MAP_COIN;
			m_tFrameKey = L"SilverCoin";
			m_iMCX = SCOINS_CX;
			m_iMCY = SCOINS_CY;
		}

		if (m_eID == MAP_ITEM)
		{
			m_eID = MAP_ITEM;
			m_iMapKey = 1;
			m_tFrameKey = L"Booster";
			m_iMCX = BOOSTER_CX;
			m_iMCY = BOOSTER_CY;
		}
	}



	if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		m_iMapKey = 2;

		if (m_eID == MAP_BLOCK)
		{
			m_eID = MAP_BLOCK;
			m_iMapKey = 2;
			m_tFrameKey = L"MidBlock";
			m_iMCX = MIDBLOCK_CX;
			m_iMCY = MIDBLOCK_CY;
		}

		if (m_eID == MAP_OBSTACLE)
		{
			m_eID = MAP_OBSTACLE;
			m_tFrameKey = L"Otte";
			m_iMCX = OTTE_CX;
			m_iMCY = OTTE_CY;
		}

		if (m_eID == MAP_COIN)
		{
			m_eID = MAP_COIN;
			m_tFrameKey = L"GoldCoin";
			m_iMCX = GCOINS_CX;
			m_iMCY = GCOINS_CY;
		}

		if (m_eID == MAP_ITEM)
		{
			m_eID = MAP_ITEM;
			m_tFrameKey = L"Big";
			m_iMCX = BIG_CX;
			m_iMCY = BIG_CY;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('3'))
	{
		m_iMapKey = 3;

		if (m_eID == MAP_COIN)
		{
			m_eID = MAP_COIN;
			m_tFrameKey = L"BigSilverCoin";
			m_iMCX = SCOINB_CX;
			m_iMCY = SCOINB_CY;
		}

		if (m_eID == MAP_ITEM)
		{
			m_eID = MAP_ITEM;
			m_tFrameKey = L"Magnet";
			m_iMCX = MAGNET_CX;
			m_iMCY = MAGNET_CY;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('4'))
	{
		m_iMapKey = 4;

		if (m_eID == MAP_COIN)
		{
			m_eID = MAP_COIN;
			m_tFrameKey = L"BigGoldCoin";
			m_iMCX = GCOINB_CX;
			m_iMCY = GCOINB_CY;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{

		switch (m_eID)
		{
		case MAP_BLOCK:
			if(m_iMapKey == 1)
			m_pMap = new CBlock;
			if (m_iMapKey == 2)
				m_pMap = new MidairBlock;
			break;

		case MAP_OBSTACLE:
			if (m_iMapKey == 1)
				m_pMap = new CObstacle;
			if (m_iMapKey == 2)
				m_pMap = new COtte;
			break;

		case MAP_COIN:
			if (m_iMapKey == 1)
				m_pMap = new CCoin;
			if (m_iMapKey == 2)
				m_pMap = new CGCoins;
			if (m_iMapKey == 3)
				m_pMap = new BigSVcoin;
			if (m_iMapKey == 4)
				m_pMap = new BigGDcoin;
			break;

		case MAP_JELLY:
			if (m_iMapKey == 1)
				m_pMap = new CJelly;
			break;

		case MAP_ITEM:
			if (m_iMapKey == 1)
				m_pMap = new Booster;
			if (m_iMapKey == 2)
				m_pMap = new Big;
			if (m_iMapKey == 3)
				m_pMap = new Magnet;
			break;

		default:
			break;
		}

		if (m_pMap) //값이 있으면
		{
			m_listMap[m_eID].push_back(m_pMap); //리스트에 넣구 
			m_listMap[m_eID].back()->Set_Pos(float(pt.x), float(pt.y));//넣은 애 위치 정해줌

		}
	

		
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		Save_Map();
	}
	if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		Load_Map();
	}
	RECT ptRect = CMouse::Get_Instance()->Get_Rect();

	//if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		//CollisionMgr::Collision_Mouse(*m_listMap, ptRect); //이건 블럭만 적용된다
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		for (int i = 0; i < MAP_END; ++i)
		{
			CollisionMgr::Collision_Mouse(m_listMap[i], ptRect);
		}
	}
	
}

	void CMapMgr::Render(HDC hDC)
	{
		if (m_tFrameKey)
		{
			HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_tFrameKey);
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);



			int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

			GdiTransparentBlt(hDC,
				static_cast<int>(pt.x / 10) * 10, //붙어있는 위치
				static_cast<int>(pt.y / 10) * 10,
				m_iMCX,
				m_iMCY,
				hMemDC,
				0, 0,
				m_iMCX,
				m_iMCY,
				ASHBLUE);
		}

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
