#include "UIBase.h"

RectCollision* UIBase::GetCollision() const
{
	return _collision.get();
}
