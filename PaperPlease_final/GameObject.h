#pragma once
#define NOMINMAX
#include <windows.h>
#include <gdiplus.h>
#include "PMath.h"
class GameObject
{
public:
    virtual void Update(float dt) = 0;//������Ʈ�ð�
    virtual void Render(Gdiplus::Graphics* g) = 0;//����(���̾ �о�ֱ�)
    virtual ~GameObject() = default;//�Ҹ���

    void SetPosition(const Vector2& pos);//��ġ����
    const Vector2& GetPosition() const;//��ġ���
protected:
    Vector2 _position;
};

