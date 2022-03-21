#pragma once


typedef struct tagInfo
{
	float fX;
	float fY;

	float fCX; //가로길이
	float fCY; //세로길이

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
	int		iFrameStart;		// 프레임 시작 시점
	int		iFrameEnd;			// 프레임 종료 지점
	int		iFrameAnimation;	// 재생할 애니메이션 인덱스
	DWORD	dwSpeed;			// 애니메이션 재생 속도
	DWORD	dwFrameTime;		// 애니메이션 시작 시간
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
