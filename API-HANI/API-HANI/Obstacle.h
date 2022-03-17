#pragma once
#include "Maps.h"
class Obstacle :
    public CMaps
{
public:
    Obstacle();
    explicit Obstacle(MAPINFO& mapInfo, INMAP eINID);
    virtual ~Obstacle();

public:
	virtual int	 Update() override;
    virtual void Render(HDC hDC) override;
    void Release();

public:
	void		Animation_Change();

	virtual void Move_Frame() override;

};

