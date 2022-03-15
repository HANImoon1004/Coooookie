#include "stdafx.h"
#include "MapMgr.h"
#include "KeyMgr.h"
#include "Obstacle.h"
CMapMgr*		CMapMgr::m_pInstance = nullptr;

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

		case MAP_OBSTACLE:
			pMap = new Obstacle(tMapInfo, eINID);
			m_listMap[MAP_OBSTACLE].push_back(pMap);
			break;
		}
	}

	MessageBox(nullptr, L">>ㅑ 로드 성공!", L"*-맵 에디터-*", MB_OK);
	CloseHandle(hFile);
}
