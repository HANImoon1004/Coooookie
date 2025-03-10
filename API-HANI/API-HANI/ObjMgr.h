#pragma once

#include "Include.h"

class CMaps;
class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Player() 
	{ 
		if (m_ObjList[OBJ_PLAYER].empty()) return nullptr;

		return m_ObjList[OBJ_PLAYER].front(); 
	}
	CObj*		Get_Target(OBJID eID, CObj* pObj);
	list<CMaps*> Get_Map(MAPID id) { return m_MapList[id]; }
	list<CObj*> Get_Obj(OBJID eID) { return m_ObjList[eID]; }

public:
	void		AddObject(OBJID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

	void		Delete_ID(OBJID eID);

private:
	list<CObj*>	m_ObjList[OBJ_END];
	list<CObj*>	m_RenderSort[RENDER_END];

	list<CMaps*> m_MapList[MAP_END];

public:
	static	CObjMgr*	Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CObjMgr;
		}

		return m_pInstance;
	}
	static	void		Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static	CObjMgr*			m_pInstance;

	
};

