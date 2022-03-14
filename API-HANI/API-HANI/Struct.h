#pragma once


typedef struct tagInfo
{
	float fX;
	float fY;

	float fCX; //���α���
	float fCY; //���α���

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
