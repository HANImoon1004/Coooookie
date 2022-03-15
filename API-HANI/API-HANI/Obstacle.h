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
    virtual void Render(HDC hDC) override;
    void Release();
};

