#include "SceneManager.h"
using namespace std;
void SceneManager::RegisterScene(SceneType type, shared_ptr<BaseScene> scene)
{
	_sceneMap[type] = scene;
	
}

void SceneManager::ChangeScene(SceneType next)
{
	if (_currentSceneType == next || _isChanging)
		return;
	_isChanging = true;
	
	if (_currentScene)
		_currentScene->Release();
	//�ؽøʿ��� ���� Ÿ�Կ� �ش��ϴ� ���� ã����
	auto it = _sceneMap.find(next);
	//ã���� ����� ���ؿ°� ���� ������ ��ȯ��
	if (it != _sceneMap.end()) {
		_currentScene = it->second.get();
	}
	else//�ƴϸ� nullptr 
	{
		_currentScene = nullptr; // �Ǵ� ���� ó��
	}
	//�װ��� �ʱ�ȭ�� �ҷ���
	if (_currentScene)
		_currentScene->Init();
	//�׸��� ���� �Է��� Ÿ���� �ؽ�Ʈ�� �ҷ�
	_currentSceneType = next;
	//�׸��� �ȹٲ۴ٰ� �˷�
	_isChanging = false;
}

void SceneManager::UpdateScene(float dt)
{
	if (_currentScene)
		_currentScene->Update(dt);
}

void SceneManager::RenderScene()
{
	if (_currentScene)
		_currentScene->Render();
}

SceneType SceneManager::GetCurrentSceneType() const
{
	return _currentSceneType;
}
void SceneManager::Release()
{
	//ó�� ���� �����ü�� make_unique�� �ϱ⶧���� ����� ���� �ʿ䰡�����¾���
}