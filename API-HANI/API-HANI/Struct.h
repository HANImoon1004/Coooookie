#pragma once


typedef struct tagInfo
{
	float fX;
	float fY;

	float fCX; //���α���
	float fCY; //���α���

	TCHAR* pFrameKey;
}INFO;


typedef	struct tagFrame
{
	DIRECTION eDir;
	DWORD	dwDelay;
	int iOffsetX;
	int iOffsetY;
	float fAngle;
	int		iFrameStar;
	int		iFrameStart;		// ������ ���� ����
	int		iFrameEnd;			// ������ ���� ����
	int		iFrameAnimation;	// ����� �ִϸ��̼� �ε���
	DWORD	dwSpeed;			// �ִϸ��̼� ��� �ӵ�
	DWORD	dwFrameTime;		// �ִϸ��̼� ���� �ð�
	UINT	tRGB;
	TCHAR* szImgKey;

	//tagFrame() {}

	tagFrame()
	: eDir(DIR_DOWN), iFrameStart(0), iFrameEnd(0), iFrameAnimation(0), dwSpeed(200), dwFrameTime(0)
	{}

	tagFrame(DIRECTION Dir, TCHAR* ImgKey, int FrameStart, int FrameEnd, int FrameAnimation, DWORD Speed, DWORD FrameTime)
	: eDir(Dir), szImgKey(ImgKey), iFrameStart(FrameStart), iFrameEnd(FrameEnd), iFrameAnimation(FrameAnimation), dwSpeed(Speed), dwFrameTime(FrameTime)
	{}
	
	
}FRAME;


typedef struct tagMapPos
{
	tagMapPos()
	{
		ZeroMemory(this, sizeof(tagMapPos));
	}

	void Set_Position(float _fX, float _fY)
	{
		fX = static_cast<int>(_fX / 10) * 10 + iCX / 2.f;
		fY = static_cast<int>(_fY / 10) * 10 + iCY / 2.f;
	}

	void Set_PosX(float _fX) { fX += _fX; }
	void Set_PosY(float _fY) { fY += _fY; }

	float fX;
	float fY;
	int		iCX;
	int		iCY;
}MAPPOS;

typedef struct tagMap
{
	tagMap()
	{
		ZeroMemory(this, sizeof(tagMap));
	}
	tagMap(int _iCX, int _iCY)
	{
		ZeroMemory(this, sizeof(tagMap));
		tPoint.iCX = _iCX;
		tPoint.iCY = _iCY;
	}
	MAPPOS tPoint;
}MAPINFO;
