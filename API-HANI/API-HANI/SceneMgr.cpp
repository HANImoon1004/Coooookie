#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr*			CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_ePreScene(SC_END), m_eCurScene(SC_LOGO)//hani 수정 03.05
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

// FSM(Finite State Machine) : 유한 상태 기계

void CSceneMgr::Set_Scene(SCENEID eScene)
{
	m_eCurScene = eScene;

	//		end, 로고 다르니까 지우고 현재가 메뉴돼 그리고 이전에 현재 넣어 그럼 이전이랑 현재 같으니까..
	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);	// 이 코드에 따른 문제가 발생할 수 있다.


		switch (m_eCurScene)
		{
		case SC_LOGO:
			m_pScene = new CLogo;
			break;

		case SC_MENU:
			m_pScene = new CMyMenu;
			break;

		case SC_STAGE01:
			m_pScene = new CStage01;
			break;

		case SC_ENDING:
			m_pScene = new Ending;
			break;

			/*	case SC_EDIT:
				m_pScene = new CMyEdit;
				break;

				case SC_FARM:
				m_pScene = new CFarm;
				break;*/
		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}




}

void CSceneMgr::Update(void)
{
	if (m_pScene)
		m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	if (m_pScene)
		m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	if (m_pScene)
		m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);

}
