#pragma once
#include "Collision.h"
//Ŭ����带 ���⼭ �����°��� ������?
//�ƴѰŰ��� ���⺸�� ui�Ŵ����� �ٷ�¹���� ��������?
//�Ѵ� �ʿ�� �ؾ��ϴ°��� �´°Ű����� �׷� �׳� define���Ϸ� �Űܼ� ������ �ϴ����� �ξ������ʳ�?
enum class ClickMode //�ϴ� ����
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
	//Ŭ������
	bool _wasClicked = false;
	//�ܺ� �ڵ��� �Ѱܹ޴� ����
	HWND l_hwnd = nullptr;

};

