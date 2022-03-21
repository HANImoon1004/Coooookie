#pragma once
#include "Maps.h"
class MidairBlock :
    public CMaps
{
public:
	MidairBlock();
	explicit MidairBlock(MAPINFO& mapInfo, INMAP eINID);
	virtual ~MidairBlock();

public:
	virtual void Render(HDC hDC) override;

	// CMaps��(��) ���� ��ӵ�
	virtual int Update() override;
};

