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

	//포인터 타입으로 반환(r_value ref로도 가능함) 변환비용을 생각하면 이동이 더 좋은방향인거같음
	//(다만 콜리전의 변형이 일어날수있기때문에 그냥 포인터타입으로 넘겨줌)
	virtual RectCollision* GetCollision() const;

protected:

	std::unique_ptr<RectCollision> _collision;
	Vector2 _pos;
	Vector2 _size;
	
};

