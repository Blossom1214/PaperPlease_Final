#pragma once
#include<string>
#include<unordered_map>
#include"ImageResource.h"
class AnimationManager
{
public:
	//singleton
	static AnimationManager& GetInstance()
	{
		static AnimationManager instance;
		return instance;
	}
	//�ִϸ��̼� �������� �������� �Լ�
	const AnimationSequence* Get(const std::wstring& name  , const std::wstring& state);
private:
	//�ִϸ��̼� ��Ͽ��Լ�
	void Register(const std::wstring& name);
	AnimationManager() = default;
	~AnimationManager() = default;
	AnimationManager(const AnimationManager&) = delete;
	AnimationManager& operator=(const AnimationManager&) = delete;
private:
	//�ִϸ��̼ǿ� ���ҽ� �����
	std::unordered_map<std::wstring, ImageResource*> _resourceRef;
};
//�ִϸ��̼��� ������ �÷����Ҷ� �ؽøʿ� ������ �ٽ� �ε��� ������