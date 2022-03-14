#pragma once
#include "Include.h"
class CMaps;

class CMapMgr
{
public:
	CMapMgr();
	~CMapMgr();


public:
	static CMapMgr* Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CMapMgr;
		return m_pInstance;
	}
	static void Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void Save_Map();
	void Load_Map();

	void Initialize();
	void Update();
	void Render(HDC hDC);
	void Release();

private:
	static CMapMgr*		m_pInstance;
	map<string, CMaps*> m_mapMap;
	list<CMaps*>		m_listMap[MAP_END];
	CMaps*	m_pMap;
	MAPID	m_eID;
	int		m_iMapKey;
	TCHAR*	m_tFrameKey;
	int		m_iMCX;
	int		m_iMCY;
};

