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
	virtual int	    Update() override;
    virtual void Render(HDC hDC) override;
    void                 Release();

public:
    void        Update_Rect() override;
	void		Animation_Change();

	virtual void Move_Frame() override;
	virtual int Late_Update(HDC hDC) override;


    void		Crushed(void);

private:
    float       m_fPower;
    float       m_fTime;
    float fDegree = 60.f;
    float fRadian = fDegree * PI / 180;
};

