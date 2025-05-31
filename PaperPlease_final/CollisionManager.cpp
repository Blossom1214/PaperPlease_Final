#include "CollisionManager.h"

bool CollisionManager::CheckClickCollision(const RectCollision& Rect)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(l_hwnd, &pt);
	_MousePointer = { static_cast<float>(pt.x),static_cast<float>(pt.y) };
	auto Rt=Rect.GetBoundary();
    bool isNowClicked = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);

    if (PtInRect(&Rt, pt) && isNowClicked && !_wasClicked)
    {
        _wasClicked = true;
        return true;
    }
    else if (!isNowClicked)
    {
        _wasClicked = false;
    }
	return false;
}

bool CollisionManager::CheckClickToCompareCollision(const RectCollision& Rect)
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(l_hwnd, &pt);
    _MousePointer = { static_cast<float>(pt.x), static_cast<float>(pt.y) };

    auto rectBoundary = Rect.GetBoundary();
    bool isNowClicked = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);

    if (PtInRect(&rectBoundary, pt) && isNowClicked && !_wasClicked)
    {
        _wasClicked = true;

        if (_compareA == nullptr)
        {
            _compareA = &Rect;
            return true;
        }
        else if (_compareB == nullptr && &Rect != _compareA)
        {
            _compareB = &Rect;
            return true;
        }
    }
    else if (!isNowClicked)
    {
        _wasClicked = false;
    }

    return false;
}
