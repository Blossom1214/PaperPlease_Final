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
	//애니메이션 시퀀스를 가져오는 함수
	const AnimationSequence* Get(const std::wstring& name  , const std::wstring& state);
private:
	//애니메이션 등록용함수
	void Register(const std::wstring& name);
	AnimationManager() = default;
	~AnimationManager() = default;
	AnimationManager(const AnimationManager&) = delete;
	AnimationManager& operator=(const AnimationManager&) = delete;
private:
	//애니메이션용 리소스 저장소
	std::unordered_map<std::wstring, ImageResource*> _resourceRef;
};
//애니메이션을 가지고 올려고할때 해시맵에 없으면 다시 로딩을 실행함