#include "UIManager.h"
#include "UIBase.h"
using namespace std;
void UIManager::UIRegister(const std::wstring& key,UIBase* ui)
{
    UIstorage[key] = ui;
}

void UIManager::Render(Gdiplus::Graphics& g)
{
    for (const auto& [key, ui] : UIstorage)
    {
           
           //ui->Render(g);
    }
}
