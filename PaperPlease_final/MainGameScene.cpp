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
              visitor->GetAnimator()->SetSequence(seqVIdle);//idle�ִϸ��̼� �������� ����
              float offset = 2.0f * i;
              int Change_sign = 1;//������ y���� ��ġ�� ��ȣ�����ؼ� �����ϱ�����
              if (i % 2 == 0)//¦����� -1�� ���ؼ� ������ �������
              {
                  Change_sign *= -1;
              }
              //�Ա����� ��ġ�� �������ִ� ����(5.0 + x���� ��ġ�� �̷�������i�� ix10.5�� �ؼ� x��ġ�� 15�� ������ y�� ��ġ��? �Ȱ����� ���� ��ȣ�� ���ؼ� ����ؾ���)
              //��ȣ ���� ������ �ʿ��ѰŰ���(�� ������ ���� Ư������ �Ѿ�� i�� ũ�⿡ ���� ������ �о����� �������� �߰�
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