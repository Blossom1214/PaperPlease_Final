#pragma once
#include "Collision.h"
//클릭모드를 여기서 나누는것이 옳은가?
//아닌거같음 여기보단 ui매니저가 다루는방식이 더옳은가?
//둘다 필요로 해야하는것이 맞는거같은데 그럼 그냥 define파일로 옮겨서 관리를 하는편이 훨씬좋지않나?
enum class ClickMode //일단 보류
{
	NORMAL,
	COMPARE
};
class CollisionManager
{
public:
	static CollisionManager& GetInstance()
	{
		static CollisionManager Instance;
		return Instance;
	}
	void SetWindowsClient(HWND hwnd) { l_hwnd = hwnd; }
	//generic mode
	bool CheckClickCollision(const RectCollision& Rect);
	//compare mode
	bool CheckClickToCompareCollision(const RectCollision& Rect);
	void SetClickMode(ClickMode mode) { _mode = mode; }
private:
	CollisionManager() = default;
	~CollisionManager() = default;
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
private:
	Vector2 _MousePointer;
	const RectCollision* _compareA = nullptr;
	const RectCollision* _compareB = nullptr;
	ClickMode _mode = ClickMode::NORMAL;
	//클릭여부
	bool _wasClicked = false;
	//외부 핸들을 넘겨받는 변수
	HWND l_hwnd = nullptr;

};

