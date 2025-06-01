#pragma once
#include "UIBase.h"
class UIStempBar : public UIBase
{
public:
	void Init();
	void Update(float dt);
	void Render(Gdiplus::Graphics* g)override;
	void ClickKey()override;
	void Release();
private:
	// 충돌체가 있어서 일단 마우스를 눌렀을때
	// 현재 열려있는지 아닌지를 확인해야함
	// 다시누르면 돌아가야하기때문
	bool _StempOn = false;


};
//이거 z오더 반드시 필요하긴 할듯 
//레이어관계가 반드시 필요함

//ui매니저는 클릭키를 함수를 받고 이제 그걸 실행하도록 하는것...
//그러면 ui매니저 업데이트는 매프레임 돌아다니면서 클릭되어서 상태를변환
//이걸 여기서 두는것보다는..? 그러면 이걸... 베이스가 가지고있는게 맞지않을까?
//그걸 오버라이드 해서 사용해야할꺼같은뎅?

