#include "UIStempBar.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include <memory>
using namespace std;
void UIStempBar::Init()
{
    ResourceManager::GetInstance().LazyloadingUIComplexSpriteJson("uiComplexSprite", "StampBar");
    _collision->SetPos(_pos);
    _collision->SetSize(_size);
}
void UIStempBar::Update(float dt)
{
	

}
void UIStempBar::Render(Gdiplus::Graphics* g)
{
    ImageResource* res = ResourceManager::GetInstance().GetImageResource(L"StampBar");
        if (!res) return;
        //���۷��� ����(z������ ���Ĵ�� �����ϱ�����)
    vector<reference_wrapper<const pair<const wstring, Parts>>> sortedParts;
    for (const auto& p : res->parts)
        sortedParts.emplace_back(p);
    //����
    sort(sortedParts.begin(), sortedParts.end(), [](const auto& a, const auto& b) {
        return a.get().second.zOrder < b.get().second.zOrder;
        });

    // ������
    for (const auto& ref : sortedParts) {
        const auto& [name, part] = ref.get();
        if (!part.img) continue;

        int drawX = static_cast<int>(_pos.x + res->pos.x+part.offset.x);
        int drawY = static_cast<int>(_pos.y + res->pos.y+part.offset.y);
        int drawW = part.img->GetWidth()*(res->scaleX);
        int drawH = part.img->GetHeight()*(res->scaleY);

        auto cmd = make_unique<DrawImageCommand>(part.img.get(), drawX, drawY, drawW, drawH);
        RenderManager::GetInstance().GetDynamicLayer().Add(std::move(cmd));
    }
    
}
void UIStempBar::ClickKey()
{
    
    _StempOn = !_StempOn;

    if (_StempOn)
        _pos.x -= 540;
    else
        _pos.x += 540;
}
void UIStempBar::Release()
{


}