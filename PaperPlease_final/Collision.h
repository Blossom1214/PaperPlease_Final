#pragma once
#include "PMath.h"
#include "framework.h"

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
	void DebugRender(Gdiplus::Graphics* g) const
	{
		/*OutputDebugStringW((L"[DebugRender] DrawRect: Pos(" +
			std::to_wstring(_pos.x) + L"," +
			std::to_wstring(_pos.y) + L"), Size(" +
			std::to_wstring(_size.x) + L"," +
			std::to_wstring(_size.y) + L")\n").c_str());*/

		Gdiplus::Pen pen(Gdiplus::Color(255, 0, 255, 0), 2.0f); // ������ ����, ���� 2px
		Gdiplus::RectF rect(_pos.x, _pos.y, _size.x, _size.y);
		g->DrawRectangle(&pen, rect);
	}
private:
	// ���� �� ��ǥ (Rect�� ������)
	Vector2 _pos;
	//���̿� �ʺ�
	Vector2 _size;


};