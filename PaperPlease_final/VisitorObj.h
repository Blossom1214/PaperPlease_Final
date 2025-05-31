#pragma once
#include "NpcObj.h"
#include <string>
namespace Gdiplus {
	class Graphics;
}
class VisitorObj : public NpcObj
{
public:
	VisitorObj(const std::wstring& imageKey);

	virtual void Update(float dt) override;
	virtual void Render(Gdiplus::Graphics* g) override;
	void StartWalkingTo(const Vector2& targetPos, float delay)
	{
		SetState(NPCState::WALKING);
		BeginMove(targetPos, delay);
	}
protected:
	//npc의 상태를 입력해주면 이제 그대로 시퀀스 키값을 반환해서 그 애니메이션을 애니메이터에게 넣게 되는과정
	virtual const AnimationSequence* GetSequenceByState(NPCState state) const override;
private:
	//리소스키
	std::wstring _imageKey;

};
