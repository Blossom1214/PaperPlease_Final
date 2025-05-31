#pragma once
#include "Collision.h"
#include "PMath.h" 
#include <memory>
namespace Gdiplus {
	class Graphics;
}
class UIBase
{
public:
	virtual ~UIBase() = default;


	virtual void Update(float dt) = 0;
	virtual void Render(Gdiplus::Graphics& g) = 0;
	virtual void ClickKey()=0;

	//������ Ÿ������ ��ȯ(r_value ref�ε� ������) ��ȯ����� �����ϸ� �̵��� �� ���������ΰŰ���
	//(�ٸ� �ݸ����� ������ �Ͼ���ֱ⶧���� �׳� ������Ÿ������ �Ѱ���)
	virtual RectCollision* GetCollision() const;

protected:

	std::unique_ptr<RectCollision> _collision;
	Vector2 _pos;
	Vector2 _size;
	
};

