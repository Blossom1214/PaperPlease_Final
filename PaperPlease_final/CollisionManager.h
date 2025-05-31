#pragma once
#include "Collision.h"
enum class ClickMode
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

