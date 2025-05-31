#pragma once
#include <unordered_map>
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
	void UIRegister(const std::wstring& key,UIBase* ui);
	void Render(Gdiplus::Graphics& g);
private:
	UIManager() = default;
	~UIManager() = default;
	UIManager(const UIManager&) = delete;
	UIManager& operator=(const UIManager&) = delete;

	std::unordered_map<std::wstring ,UIBase*> UIstorage;

};

