#pragma once
#include <unordered_map>
#include "framework.h"
#include <string>
namespace Gdiplus {
	class Graphics;
}
class UIBase;
class UIManager
{
public:
	static UIManager& GetInstance()
	{
		static UIManager instance;
		return instance;
	}
	//������ UI���
	void UIRegister(const std::wstring& key, std::unique_ptr<UIBase> ui);
	void Update(float dt);
	void Render(Gdiplus::Graphics* g);
private:
	UIManager() = default;
	~UIManager() = default;
	UIManager(const UIManager&) = delete;
	UIManager& operator=(const UIManager&) = delete;

	std::unordered_map<std::wstring , std::unique_ptr<UIBase>> UIstorage;
};

//������ ��� json ���Ͽ��� �Ľ��ؿö� ��Ÿ������ �������� �Ľ��� ���� �Ǵµ� �׷������� ���� �ε��� ���� ���Ŀ� 
//�������� ������� �Ľ��� �;��ϴ°��� ���� ������ 
//��ǻ� �׳� complexUIimage�Ľ� ����� ���λ���ؼ� �����;��ϴ� �����ΰŰ���

//�̰� ��ǲ�Ŵ����� �ΰ� ��ǲ�Ŵ����� ������ ������Ʈ ��������  Ŭ�������� �Է°��� �����ϰ�?
//�� �Է°��� �ش��ϴ� ��尡 ��� ����̳Ŀ� ���� �ݸ��� �Ŵ����� �����ϴ� ������ �̷�����
//�� ��ǲ�Ŵ����� ���� �����ϸ� ���Ŵ����� ������Ʈ ������ �����ϸ� ������Ʈ�� �ؾ��ϴ� ������ �̷���� ����
//�׷��� uimamager�� ��� �ҷ��� �ϴ°�?
//�����ȿ��� �Ҹ������� ���� �ش� ui�� ���������� Ŭ��Ű�� Ȯ���ϴ� ������ �������Ӹ��� ���������
//��ǲ�Ŵ����� �ʿ��Ѱ�?
//������Ʈ�� �ƴ϶� �׳� Ŭ��Ű�� ȣ���ϸ� �ȵǴ°ǰ������� ���
//ȣ���ص� �ȴ� �ٸ� ��������