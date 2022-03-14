#pragma once
#include "Include.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize(); //데이터 초기화
	void Update(); //매 프레임마다 데이터 갱신
	void Late_Update(); // 업데이트 연산 끝난 뒤 호출, 완성된 객체들의 정보 참조/각종 객체 상태 표현
	void Render(); // 매 프레임마다 출력하는 함수
	void Release(); //동적할당한 메모리를 해제하는 함수

private:
	HDC			m_DC;
	DWORD		m_dwTime;
	int				m_iFPS;
	TCHAR		m_szFPS[16];

};

