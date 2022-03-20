#pragma once
#include "Maps.h"
class CObstacle :
	public CMaps
{
public:
	CObstacle();
	explicit CObstacle(MAPINFO& mapInfo, INMAP eINID);
	virtual ~CObstacle();

public:
	virtual void Render(HDC hDC) override;

	// CMaps을(를) 통해 상속됨
	virtual int Update() override;
};

