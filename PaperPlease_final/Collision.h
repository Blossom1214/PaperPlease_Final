#pragma once
#include "PMath.h"
#include <Windows.h>

class RectCollision
{
public:
	void SetPos(const Vector2& pos) { _pos = pos; }
	const Vector2& GetPos()const { return _pos; }

	void SetSize(const Vector2& size) { _size = size; }
	const Vector2& GetSize()const { return _size; }

	Vector2 GetCenterPos()const
	{
		float fWidth = (_pos.x + _size.x) * 0.5f;
		float fHeight = (_pos.y + _size.y) * 0.5f;
		return { fWidth,fHeight };
	}

	RECT GetBoundary()const
	{
		RECT rt{};
		rt.left = static_cast<LONG>(_pos.x);
		rt.top = static_cast<LONG>(_pos.y);
		rt.right = static_cast<LONG>(_pos.x + _size.x);
		rt.bottom = static_cast<LONG>(_pos.y + _size.y);

		return rt;
	}
private:
	// 왼쪽 위 좌표 (Rect의 기준점)
	Vector2 _pos;
	//높이와 너비
	Vector2 _size;


};