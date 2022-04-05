#pragma once
#include "Maps.h"
#include "Block.h"

class CMapMgr
{
public:
	CMapMgr();
	~CMapMgr();

public:
	void Initialize();
	void	Update();
	void Late_Update(HDC hDC);
	void Render(HDC hDC);
	void Release(); 
	void Load_Map();

public:
	list<CMaps*>	Get_MapList(MAPID eID) { return m_listMap[eID]; }
	void	Set_Magnet(bool swit);

public:
	static CMapMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new  CMapMgr;
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
private:
	static CMapMgr*			m_pInstance;
	list<CMaps*>		m_listMap[MAP_END];


};

