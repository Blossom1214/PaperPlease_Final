#pragma once
#include "SceneType.h"
#include "BaseScene.h"
#include <unordered_map>
#include <memory>
class SceneManager
{
public:
	static SceneManager& GetInstance() //싱글턴화 됨
	{
		static SceneManager instance;
		return instance;
	}
	//초기 씬 등록
	void RegisterScene(SceneType type, std::shared_ptr<BaseScene> scene);
	//씬 전환
	void ChangeScene(SceneType next);
	//현재씬의 업데이트호출
	void UpdateScene(float dt);
	//현재씬의 렌더를 호출
	void RenderScene();
	//현재씬이 어떤 씬타입인지?
	SceneType GetCurrentSceneType() const;
	//초기화
	void Release();
private:
	//싱글턴 하기위한 생성자들과 연산자오버로딩 날리기
	SceneManager() = default;
	~SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
private:
	//씬타입을 해시키로 가지는 추상화된 base scene 포인터(shared pointer)
	//(근데 이거 유니크로 바꾸어도 문제가 없을꺼같긴한데)
	//사실 논리적으로는 각씬을 ...음...
	std::unordered_map<SceneType, std::shared_ptr<BaseScene>> _sceneMap;
	//현재씬을 저장하는 목적으로 쓰기위해 추상화된 씬 포인터를 가지게되는 변수임
	BaseScene* _currentScene = nullptr;
	//현재씬의 타입을 저장하는 변수
	SceneType _currentSceneType= SceneType::TITLE;
	//전환상태인지? (이걸두는 이유는 다음씬으로 전환하기 직전에..
	//다음 씬에게 현재씬의 정보를 
	bool _isChanging = false;
};

//씬 매니저가 해야하는 역할들
//새로운 씬으로 들어가면 초기화 함수를 호출함
//씬 교체
//해당씬의 업데이트와 렌더 호출
//해당씬의 정보날리기..