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
    POINT   m_tCenter; // ���� �߽�
    float       m_fRotAngle; // ������ ������ ����
    float       m_fRotSpeed; //�����Ӹ��� ������ ������Ű�� ���� ���
    float       m_fRotDistance; //�������κ��� �Ÿ�

    bool        m_bRotation;
};

