#include "CollisionManager.h"

bool CollisionManager::CheckClickCollision(const RectCollision& Rect)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(l_hwnd, &pt);
	_MousePointer = { static_cast<float>(pt.x),static_cast<float>(pt.y) };
	auto Rt=Rect.GetBoundary();
    bool isInside = PtInRect(&Rt, pt);
    bool isNowClicked = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
    bool canTrigger = isInside && isNowClicked && !_wasClicked;
    /*OutputDebugStringW((L"Rect: " +
        std::to_wstring(Rt.left) + L"," +
        std::to_wstring(Rt.top) + L"," +
        std::to_wstring(Rt.right) + L"," +
        std::to_wstring(Rt.bottom) + L"\n").c_str());

    OutputDebugStringW((L"Mouse: " +
        std::to_wstring(pt.x) + L"," +
        std::to_wstring(pt.y) + L"\n").c_str());*/
    if (isInside)
        OutputDebugStringW(L"[INFO] ���콺�� �ڽ� �ȿ� ����\n");
    if (isNowClicked)
        OutputDebugStringW(L"[INFO] ��Ŭ�� ��\n");
    if (_wasClicked)
        OutputDebugStringW(L"[INFO] �̹� Ŭ�� ó����\n");

  
    
    if (canTrigger)
    {
        _wasClicked = true;
        OutputDebugStringW(L"[EVENT] Ŭ�� �浹 �߻�!\n");
       ;
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
