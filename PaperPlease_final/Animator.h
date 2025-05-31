#pragma once
#include "AnimationManager.h"
#include <memory>
#include "IPlaybackPolicy.h"
#include <Windows.h>
class Animator
{
public:
	Animator() = default;

	void SetSequence(const AnimationSequence* seq);//������ ������ �����ʱ�ȭ
	void Update(float deltaTime);//�ð�����+��������ȯ


	const RECT& GetCurrentRect() const;//���� �������� �߶� �簢�� ��ȯ
	const AnimationSequence* GetCurrentSequence() const { return _sequence; };//������ ��ȯ(�б�)

	void Play();//�������
	void Pause();//�Ͻ�����
	void Stop();//������ ó������

	

	bool IsPlaying() const { return _playing; }//���� ����������� ��ȯ

	void SetPlaybackPolicy(std::unique_ptr<IPlaybackPolicy> policy);//������� �����?!

private:
	const AnimationSequence* _sequence = nullptr;//���� ������� �ִϸ��̼�

	int _currentFrameIndex =0;//���� �������ε���
	float _elapsedTime = 0.0f;//�����ð�(��������ȯ)
	bool _playing = true; //�Ͻ�����/���

	std::unique_ptr<IPlaybackPolicy> _policy;
};


