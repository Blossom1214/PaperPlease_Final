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
	//최초의 UI등록
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

//현재의 고민 json 파일에서 파싱해올때 메타데이터 형식으로 파싱해 오게 되는데 그러면이제 최초 로딩때 파츠 형식에 
//파츠들은 어떤식으로 파싱해 와야하는가에 대한 문제로 
//사실상 그냥 complexUIimage파싱 방식을 따로사용해서 가져와야하는 문제인거같음