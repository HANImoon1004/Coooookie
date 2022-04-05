#pragma once

#include "Logo.h"
#include "MyMenu.h"
#include "Stage01.h"
#include "Ending.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	SCENEID		Get_SceneID(void) { return m_eCurScene; }
	CScene* Get_CScene(void) { return m_pScene; }
	void		Set_PlayerKey(TCHAR* pPlayerKey) { m_PlayerKey = pPlayerKey; }

	void		Set_Scene(SCENEID eScene);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	static	CSceneMgr*	Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CSceneMgr;
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
	static	CSceneMgr*			m_pInstance;
	CScene*						m_pScene = nullptr;

	SCENEID						m_eCurScene;		// «ˆ¿Á¿« æ¿ id
	SCENEID						m_ePreScene;		// ¿Ã¿¸ æ¿ id

	TCHAR*						m_PlayerKey;

};

