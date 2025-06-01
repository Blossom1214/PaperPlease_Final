#pragma once
#include "UIBase.h"
#include <memory>
class UIstemp;
class UIStempBar : public UIBase
{
public:
	void Init();
	void Update(float dt);
	void Render(Gdiplus::Graphics* g)override;
	void ClickKey()override;
	void Release();
private:
	// �浹ü�� �־ �ϴ� ���콺�� ��������
	// ���� �����ִ��� �ƴ����� Ȯ���ؾ���
	// �ٽô����� ���ư����ϱ⶧��
	bool _StempOn = false;
	//std::unique_ptr<UIstemp> _stamp_approve;
	//std::unique_ptr<UIstemp> _stamp_deny;

};
//�̰� z���� �ݵ�� �ʿ��ϱ� �ҵ� 
//���̾���谡 �ݵ�� �ʿ���

//ui�Ŵ����� Ŭ��Ű�� �Լ��� �ް� ���� �װ� �����ϵ��� �ϴ°�...
//�׷��� ui�Ŵ��� ������Ʈ�� �������� ���ƴٴϸ鼭 Ŭ���Ǿ ���¸���ȯ
//�̰� ���⼭ �δ°ͺ��ٴ�..? �׷��� �̰�... ���̽��� �������ִ°� ����������?
//�װ� �������̵� �ؼ� ����ؾ��Ҳ�������?

