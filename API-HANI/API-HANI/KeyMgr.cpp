#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_bKeyState, sizeof(m_bKeyState));
}


CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::Key_Pressing(int _Key)
{
	if (GetAsyncKeyState(_Key) & 0x8000)
		return true;

	return false;
}

bool CKeyMgr::Key_Down(DWORD dwKey)
{
	//if (!m_bKeyState[_Key] && (GetAsyncKeyState(_Key) & 0x8000))
	//{
	//	m_bKeyState[_Key] = !m_bKeyState[_Key];
	//	return true;
	//}

	//if (m_bKeyState[_Key] && !(GetAsyncKeyState(_Key) & 0x8000))
	//	m_bKeyState[_Key] = !m_bKeyState[_Key];

	
	//return false;
	if ((m_dwKey & dwKey) && !(m_dwKeyDOWN & dwKey))
	{
		m_dwKeyDOWN |= dwKey;
		return true;
	}
	else if (!(m_dwKey & dwKey) && (m_dwKeyDOWN & dwKey))
	{
		m_dwKeyDOWN ^= dwKey;
		return false;
	}
	return false;
}
// ¥≠∑∂¥Ÿ∞° ∂√¿ª ∂ß
bool CKeyMgr::Key_Up(int _Key)
{
	if (m_bKeyState[_Key] && !(GetAsyncKeyState(_Key) & 0x8000))
	{
		m_bKeyState[_Key] = !m_bKeyState[_Key];
		return true;
	}

	if (!m_bKeyState[_Key] && (GetAsyncKeyState(_Key) & 0x8000))
		m_bKeyState[_Key] = !m_bKeyState[_Key];

	return false;
}

bool CKeyMgr::Key_DdoDown(int _Key)
{
	if (m_bKeyState[_Key] && (GetAsyncKeyState(_Key) & 0x8001))
	{
		m_bKeyState[_Key] = m_bKeyState[_Key];
		return true;
	}

	if (!m_bKeyState[_Key] && !(GetAsyncKeyState(_Key) & 0x8001))
		m_bKeyState[_Key] = !m_bKeyState[_Key];

	return false;
}

void CKeyMgr::Update(void)
{
	m_dwKey = 0;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwKey |= KEY_SPACE;
}


