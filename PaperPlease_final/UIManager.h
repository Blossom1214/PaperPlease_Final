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
	void SetWindowsClient(HWND hwnd) { l_hwnd = hwnd; }
	void UIRegister(const std::wstring& key,UIBase* ui);
	void Update(float dt);
	void Render(Gdiplus::Graphics& g);
	void ClickKey();
private:
	UIManager() = default;
	~UIManager() = default;
	UIManager(const UIManager&) = delete;
	UIManager& operator=(const UIManager&) = delete;

	std::unordered_map<std::wstring ,UIBase*> UIstorage;
	HWND l_hwnd = nullptr;
};

//������ ��� json ���Ͽ��� �Ľ��ؿö� ��Ÿ������ �������� �Ľ��� ���� �Ǵµ� �׷������� ���� �ε��� ���� ���Ŀ� 
//�������� ������� �Ľ��� �;��ϴ°��� ���� ������ 
//��ǻ� �׳� complexUIimage�Ľ� ����� ���λ���ؼ� �����;��ϴ� �����ΰŰ���