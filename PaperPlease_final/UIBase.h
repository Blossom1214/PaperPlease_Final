#pragma once
#include "Collision.h"
#include "PMath.h" 
#include <memory>
class UIBase
{
	virtual void ClickKey();

protected:
	Vector2 _pos;
	Vector2 _size;
	
};

