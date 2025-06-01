#include "UIStempBar.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include <memory>
using namespace std;
void UIStempBar::Init()
{
    ResourceManager::GetInstance().LazyloadingUIComplexSpriteJson("uiComplexSprite", "StampBar");
    _collision = std::make_unique<RectCollision>();
    ImageResource* res = ResourceManager::GetInstance().GetImageResource(L"StampBar");
    if (!res) return;
    _pos = Vector2{ static_cast<float>(res->pos.x), static_cast<float>(res->pos.y) };
    _size = Vector2{ 560.0f, 110.0f };
    _collision->SetPos(_pos);
    _collision->SetSize(_size);
}
void UIStempBar::Update(float dt)
{
   
    if (CollisionManager::GetInstance().CheckClickCollision(*_collision))
    {
        ClickKey();
    }

}
void UIStempBar::Render(Gdiplus::Graphics* g)
{
    ImageResource* res = ResourceManager::GetInstance().GetImageResource(L"StampBar");
        if (!res) return;
        //레퍼런스 래핑(z오더의 형식대로 정렬하기위함)
    vector<reference_wrapper<const pair<const wstring, Parts>>> sortedParts;
    for (const auto& p : res->parts)
        sortedParts.emplace_back(p);
    //정렬
    sort(sortedParts.begin(), sortedParts.end(), [](const auto& a, const auto& b) {
        return a.get().second.zOrder < b.get().second.zOrder;
        });

    // 렌더링
    for (const auto& ref : sortedParts) {
        const auto& [name, part] = ref.get();
        if (!part.img) continue;

        int drawX = static_cast<int>(_pos.x+part.offset.x);
        int drawY = static_cast<int>(_pos.y+part.offset.y);
        int drawW = part.img->GetWidth()*(res->scaleX);
        int drawH = part.img->GetHeight()*(res->scaleY);

        auto cmd = make_unique<DrawImageCommand>(part.img.get(), drawX, drawY, drawW, drawH);
        RenderManager::GetInstance().GetDynamicLayer().Add(std::move(cmd));
    }
   
    _collision->DebugRender(g);
    
}
void UIStempBar::ClickKey()
{
    
    _StempOn = !_StempOn;

    if (_StempOn) {
        _pos.x -= 540;
    }
    else
    {
        _pos.x += 540;
    }
    _collision->SetPos(_pos);
    _collision->SetSize(_size);
}
void UIStempBar::Release()
{


}