#pragma once
#include "Maps.h"
class MidBlock :
    public CMaps
{
public:
	MidBlock();
	explicit MidBlock(MAPINFO& mapInfo, INMAP eINID);
	virtual ~MidBlock();

public:
	virtual int	 Update() override;
	virtual void Render(HDC hDC) override;
	void Release();

public:
	virtual void Animation_Change() override;
	virtual void Move_Frame() override;


	// CMaps��(��) ���� ��ӵ�
	virtual int Late_Update(HDC hDC) override;

};

