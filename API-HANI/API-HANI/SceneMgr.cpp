#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr*			CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_ePreScene(SC_END), m_eCurScene(SC_LOGO)//hani ���� 03.05
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

// FSM(Finite State Machine) : ���� ���� ���

void CSceneMgr::Set_Scene(SCENEID eScene)
{
	m_eCurScene = eScene;

	//		end, �ΰ� �ٸ��ϱ� ����� ���簡 �޴��� �׸��� ������ ���� �־� �׷� �����̶� ���� �����ϱ�..
	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);	// �� �ڵ忡 ���� ������ �߻��� �� �ִ�.


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
