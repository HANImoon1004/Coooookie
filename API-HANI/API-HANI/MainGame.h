#pragma once
#include "Include.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize(); //������ �ʱ�ȭ
	void Update(); //�� �����Ӹ��� ������ ����
	void Late_Update(); // ������Ʈ ���� ���� �� ȣ��, �ϼ��� ��ü���� ���� ����/���� ��ü ���� ǥ��
	void Render(); // �� �����Ӹ��� ����ϴ� �Լ�
	void Release(); //�����Ҵ��� �޸𸮸� �����ϴ� �Լ�

private:
	HDC			m_DC;
	DWORD		m_dwTime;
	int				m_iFPS;
	TCHAR		m_szFPS[16];

};

