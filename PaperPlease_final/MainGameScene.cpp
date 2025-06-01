#include "MainGameScene.h"
#include "StaticRenderCheckPoint.h"
#include "ResourceManager.h"
#include "DoubleBufferManager.h"
#include "RenderManager.h"
#include "UIManager.h"
#include "UIStempBar.h"
using namespace std;
using namespace Gdiplus;
extern DoubleBufferManager backBuffer;
void MainGameScene::Init()
{
    AddDayCount();

    InitStaticRenderLayer(ResourceManager::GetInstance().GetImageResource(L"CheckpointBack"));
    InitStaticRenderLayer(ResourceManager::GetInstance().GetImageResource(L"BoothWall"));
    InitStaticRenderLayer(ResourceManager::GetInstance().GetImageResource(L"Desk"));

    const AnimationSequence* seqSWalk = AnimationManager::GetInstance().Get(L"soldier", L"walk");
    const AnimationSequence* seqVIdle = AnimationManager::GetInstance().Get(L"visitor", L"idle");
  
    auto stampBar = make_unique<UIStempBar>();
    stampBar->Init();
    UIManager::GetInstance().UIRegister(L"StampBar", std::move(stampBar));

    ResourceManager::GetInstance().LazyloadingUIComplexSpriteJson("uiComplexSprite", "StampBar");

    
    
    

      if (_DayCount <= 2) {
          auto soldier = make_unique<VisitorObj>(L"soldier");
          soldier->GetAnimator()->SetSequence(seqSWalk);
          soldier->SetPosition({ 1100.0f, -100.0f });
          soldier->StartWalkingTo({ 1100.0f, 100.0f }, 0.f);
          _VisitorNpcs.emplace_back(move(soldier));
      }
      if (_DayCount == 3)
      {
          for (int i = 0; i < 5; ++i) {
              auto soldier = make_unique<SoldierObj>(L"soldier");
              soldier->GetAnimator()->SetSequence(seqSWalk);
              soldier->SetPosition({ 1100.0f, -100.0f });
              if (i > 2)
              {
                  soldier->SetPosition({ 275.0f, -100.0f });
              }
              _SoldierNpcs.emplace_back(move(soldier));
          }
          _SoldierNpcs[0]->StartWalkingTo({ 1100.0f, 90.0f }, 1.5f);
          _SoldierNpcs[1]->StartWalkingTo({ 1100.0f, 40.0f }, 2.0f);
          _SoldierNpcs[2]->StartWalkingTo({ 1100.0f, 140.0f }, 0.f);
          _SoldierNpcs[3]->StartWalkingTo({ 275.0f, 100.0f }, 0.f);
          _SoldierNpcs[4]->StartWalkingTo({ 275.0f, 50.0f }, 1.5f);
          for (int i = 0; i < 30; ++i) {
              auto visitor = make_unique<VisitorObj>(L"visitor");
              visitor->GetAnimator()->SetSequence(seqVIdle);//idle애니메이션 시퀀스를 실행
              float offset = 2.0f * i;
              int Change_sign = 1;//포지션 y값의 위치를 부호반전해서 설정하기위함
              if (i % 2 == 0)//짝수라면 -1을 곱해서 음수로 만들어줌
              {
                  Change_sign *= -1;
              }
              //입국자의 위치를 설정해주는 로직(5.0 + x축의 위치를 이렇게조정i의 ix10.5를 해서 x위치를 15로 잡고시작 y의 위치는? 똑같으나 이제 부호를 곱해서 사용해야함)
              //부호 높이 보정이 필요한거같음(다 좋은데 이제 특정값을 넘어가면 i의 크기에 따라서 간격이 넓어지는 문제점을 발견
              if (i <= 10)
                  visitor->SetPosition({ (5.0f + offset + static_cast<float>(i) * 10.5f), (38.375f + (0.75f * Change_sign)) });
              if (i > 10)
              {
                  visitor->SetPosition({ (145.f), (42.5f + offset + (0.75f * Change_sign)) });
              }
              _VisitorNpcs.emplace_back(move(visitor));
          }
      }



 }

void MainGameScene::Update(float dt)
{
    for (auto& npc : _SoldierNpcs)
    {
        npc->Update(dt);
    }
    for (auto& npc : _VisitorNpcs)
    {
        npc->Update(dt);
    }
    UIManager::GetInstance().Update(dt);
}
void MainGameScene::Render()
{
    for (auto& npc : _SoldierNpcs)
    {
        npc->Render(backBuffer.GetGraphics());
    }
    for (auto& npc : _VisitorNpcs)
    {
        npc->Render(backBuffer.GetGraphics());
    }
    UIManager::GetInstance().Render(backBuffer.GetGraphics());
}
void  MainGameScene::Release()
{
    
    _SoldierNpcs.clear();
    _VisitorNpcs.clear();
    
    RenderManager::GetInstance().ClearPerFrame();
}