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

CMapMgr*	CMapMgr::m_pInstance = nullptr;

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
		MessageBox(nullptr, __T("���� ���Ф�_��"), __T("��"), MB_OK);
		return;
	}
	DWORD dwByte = 0;

	for (int i = 0; i < MAP_END; ++i)
	{
		for (auto& iter : m_listMap[i])
		{
			WriteFile(hFile, iter->Get_MapInfo(), sizeof(MAPINFO), &dwByte, nullptr);
			WriteFile(hFile, iter->Get_INID(), sizeof(int), &dwByte, nullptr); //��� Q
		}
	}

	MessageBox(nullptr, L"�� ���� ����!", L"*-��-*", MB_OK);
	CloseHandle(hFile);
}

void CMapMgr::Load_Map()
{
	HANDLE hFile = CreateFile(__T("../Data/Map.dat"),
		GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(nullptr, __T("�ε� ���Ф�_��"), __T("��"), MB_OK);
		return;
	}
	CMaps*	pMap = nullptr;
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
		case MAP_BLOCK:
			pMap = new CBlock(tMapInfo, eINID);
			m_listMap[MAP_BLOCK].push_back(pMap);
			break;
		}
	}

	MessageBox(nullptr, L">>�� �ε� ����!", L"*-�� ������-*", MB_OK);
	CloseHandle(hFile);
}

void CMapMgr::Initialize()
{
}

void CMapMgr::Update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= CScrollMgr::Get_Instance()->Get_ScrollY();

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-10);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(+10);

	if (CKeyMgr::Get_Instance()->Key_Down('B'))//��
	{
		m_eID = MAP_BLOCK;
		m_iMapKey = 1;
		m_tFrameKey = L"Block";
		m_iMCX = BLOCK_CX;
		m_iMCY = BLOCK_CY;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('C'))//�����
	{
		m_eID = MAP_OBSTACLE;
		m_iMapKey = 1;
		m_tFrameKey = L"Cat";
		m_iMCX = CAT_CX;
		m_iMCY = CAT_CY;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('D'))//�ǹ� ����
	{
		m_eID = MAP_COIN;
		m_iMapKey = 1;
		m_tFrameKey = L"SilverCoin";
		m_iMCX = SCOINS_CX;
		m_iMCY = SCOINS_CY;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		m_iMapKey = 1;

		if (m_eID == MAP_OBSTACLE)
		{
			m_eID = MAP_OBSTACLE;
			m_tFrameKey = L"Otte";
			m_iMCX = OTTE_CX;
			m_iMCY = OTTE_CY;
		}

		if (m_eID == MAP_COIN)
		{
			m_tFrameKey = L"SilverCoin";
			m_iMCX = SCOINS_CX;
			m_iMCY = SCOINS_CY;
		}
	}


	if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		m_iMapKey = 2;

		if (m_eID == MAP_OBSTACLE)
		{
			m_eID = MAP_OBSTACLE;
			m_tFrameKey = L"Otte";
			m_iMCX = OTTE_CX;
			m_iMCY = OTTE_CY;
		}

		if (m_eID == MAP_COIN)
		{
			m_tFrameKey = L"GoldCoin";
			m_iMCX = GCOINS_CX;
			m_iMCY = GCOINS_CY;
		}
	}


	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		switch (m_eID)
		{
		case MAP_BLOCK:
			m_pMap = new CBlock;
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
			break;
		}

		if (m_pMap) //���� ������
		{
			m_listMap[m_eID].push_back(m_pMap); //����Ʈ�� �ֱ� 
			m_listMap[m_eID].back()->Set_Pos(float(pt.x), float(pt.y));//���� �� ��ġ
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
			static_cast<int>(pt.x / 10) * 10, //�پ��ִ� ��ġ
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
