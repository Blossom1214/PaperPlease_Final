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

//현재의 고민 json 파일에서 파싱해올때 메타데이터 형식으로 파싱해 오게 되는데 그러면이제 최초 로딩때 파츠 형식에 
//파츠들은 어떤식으로 파싱해 와야하는가에 대한 문제로 
//사실상 그냥 complexUIimage파싱 방식을 따로사용해서 가져와야하는 문제인거같음

//이게 인풋매니저를 두고 인풋매니저가 각씬의 업데이트 구간에서  클릭에대한 입력값을 전달하고?
//그 입력값에 해당하는 모드가 어떠한 모드이냐에 따라서 콜리전 매니저도 반응하는 구조를 이루어야함
//즉 인풋매니저가 따로 존재하며 씬매니저의 업데이트 구간에 간섭하며 업데이트를 해야하는 구조로 이루어져 있음
//그러면 uimamager는 어디서 불려야 하는가?
//각씬안에서 불리워지며 이제 해당 ui의 렌더과정과 클릭키를 확인하는 과정을 매프레임마다 거쳐줘야함
//인풋매니저가 필요한가?
//업데이트가 아니라 그냥 클릭키를 호출하면 안되는건가에대한 고민
//호출해도 된다 다만 불편해짐