#pragma once
#include "Maps.h"
class Otte :
    public CMaps
{
public:
    Otte();
    explicit Otte(MAPINFO& mapInfo, INMAP eINID);
    virtual ~Otte();

public:
    virtual int	 Update() override;
    virtual void Render(HDC hDC) override;
    void Release();
    void        Update_Rect() override;
    void		Animation_Change();

    virtual void Move_Frame() override;
    virtual int Late_Update(HDC hDC) override;


public:
    void            Set_Rotation() { m_bRotation = true; }
private:
    POINT   m_tCenter; // 공전 중심
    float       m_fRotAngle; // 공전을 수행할 각도
    float       m_fRotSpeed; //프레임마다 각도를 증가시키기 위한 상수
    float       m_fRotDistance; //중점으로부터 거리

    bool        m_bRotation;
};

