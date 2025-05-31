#pragma once
#include <memory>
#include <functional>
enum class SceneType
{
	TITLE,
	SINARIO,
	MAINGAME,
	RESULT,
	NEWS,
	ENDING
};
namespace std {//�ؽ����̺���� ���� ������ ����... ���ø�Ư��ȭ�� �߰���...
	template<>
	struct hash<SceneType> {
		size_t operator()(const SceneType& p) const noexcept
		{
			return static_cast<size_t>(p);
		}
	};
}