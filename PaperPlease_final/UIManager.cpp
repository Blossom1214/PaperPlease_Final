#include "UIManager.h"
#include "UIBase.h"
using namespace std;
void UIManager::UIRegister(const std::wstring& key,UIBase* ui)
{
    UIstorage[key] = ui;
}

void UIManager::Update(float dt)
{
    for (const auto& [key, ui] : UIstorage)
    {
        ui->Update(dt);
    }
}

void UIManager::Render(Gdiplus::Graphics& g)
{
    for (const auto& [key, ui] : UIstorage)
    {
           ui->Render(g);
    }
}

void UIManager::ClickKey()
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(l_hwnd, &pt);
    Vector2 mousePos{ static_cast<float>(pt.x), static_cast<float>(pt.y) };
}
