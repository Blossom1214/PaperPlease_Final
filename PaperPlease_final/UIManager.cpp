#include "UIManager.h"
#include "UIBase.h"
using namespace std;
void UIManager::UIRegister(const wstring& key, unique_ptr<UIBase> ui)
{
    UIstorage[key] = std::move(ui);
}

void UIManager::Update(float dt)
{
    for (const auto& [key, ui] : UIstorage)
    {
        ui->Update(dt);
       
    }
}

void UIManager::Render(Gdiplus::Graphics* g)
{
    for (const auto& [key, ui] : UIstorage)
    {
          ui->Render(g);
    }
}