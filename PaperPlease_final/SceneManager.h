#pragma once
#include "SceneType.h"
#include "BaseScene.h"
#include <unordered_map>
#include <memory>
class SceneManager
{
public:
	static SceneManager& GetInstance() //�̱���ȭ ��
	{
		static SceneManager instance;
		return instance;
	}
	//�ʱ� �� ���
	void RegisterScene(SceneType type, std::shared_ptr<BaseScene> scene);
	//�� ��ȯ
	void ChangeScene(SceneType next);
	//������� ������Ʈȣ��
	void UpdateScene(float dt);
	//������� ������ ȣ��
	void RenderScene();
	//������� � ��Ÿ������?
	SceneType GetCurrentSceneType() const;
	//�ʱ�ȭ
	void Release();
private:
	//�̱��� �ϱ����� �����ڵ�� �����ڿ����ε� ������
	SceneManager() = default;
	~SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
private:
	//��Ÿ���� �ؽ�Ű�� ������ �߻�ȭ�� base scene ������(shared pointer)
	//(�ٵ� �̰� ����ũ�� �ٲپ ������ �����������ѵ�)
	//��� �������δ� ������ ...��...
	std::unordered_map<SceneType, std::shared_ptr<BaseScene>> _sceneMap;
	//������� �����ϴ� �������� �������� �߻�ȭ�� �� �����͸� �����ԵǴ� ������
	BaseScene* _currentScene = nullptr;
	//������� Ÿ���� �����ϴ� ����
	SceneType _currentSceneType= SceneType::TITLE;
	//��ȯ��������? (�̰ɵδ� ������ ���������� ��ȯ�ϱ� ������..
	//���� ������ ������� ������ 
	bool _isChanging = false;
};

//�� �Ŵ����� �ؾ��ϴ� ���ҵ�
//���ο� ������ ���� �ʱ�ȭ �Լ��� ȣ����
//�� ��ü
//�ش���� ������Ʈ�� ���� ȣ��
//�ش���� ����������..