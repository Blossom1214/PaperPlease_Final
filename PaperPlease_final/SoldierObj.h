#pragma once
#include "NpcObj.h"
#include <string>
namespace Gdiplus {
	class Graphics;
}
class SoldierObj : public NpcObj
{
public:
	SoldierObj(const std::wstring& imageKey);

	virtual void Update(float dt) override;
	virtual void Render(Gdiplus::Graphics* g) override;
	void StartWalkingTo(const Vector2& targetPos,float delay)
	{
		SetState(NPCState::WALKING);
		BeginMove(targetPos, delay);
	}
protected:
	//npc�� ���¸� �Է����ָ� ���� �״�� ������ Ű���� ��ȯ�ؼ� �� �ִϸ��̼��� �ִϸ����Ϳ��� �ְ� �Ǵ°���
	virtual const AnimationSequence* GetSequenceByState(NPCState state) const override;
private:
	//���ҽ�Ű
	std::wstring _imageKey;

};
//������ ������ ���ο�
//���ε��� ���� ��𼭺��� ������ ���������ϴ���?
//�����ӿ� ���� ���������� ������ �̹� �Ͽ���
//�׷� ���� �ؾ��ϴ°� ���������Ȱ��� Ȱ���ؼ�