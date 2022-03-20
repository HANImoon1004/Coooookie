#pragma once
#include "Maps.h"
class COtte :
	public CMaps
{
public:
	COtte();
	explicit COtte(MAPINFO& mapInfo, INMAP eINID);
	virtual ~COtte();



public:
	virtual void Render(HDC hDC) override;


	// CMaps을(를) 통해 상속됨
	virtual int Update() override;

};

