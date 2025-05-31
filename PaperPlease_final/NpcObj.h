#pragma once
#include "GameObject.h"
#include "NPCState.h"
#include "Animator.h"
#include <memory>
#include <string>
class NpcObj : public GameObject
{
public:
	virtual void Update(float dt) override =0;
	virtual void Render(Gdiplus::Graphics* g) override = 0;
	void SetAnimator(std::unique_ptr<Animator> animator) { _animator = move(animator); }
	Animator* GetAnimator() const { return _animator.get(); }
	NPCState GetState()const { return _state; }
protected:
	//�̵� �Լ�
	bool MoveTowardsTarget(float dt);
	//������ ���¸� �������ִ� �Լ�
	void SetState(NPCState state);
	//�������� �ٶ󺸴���?
	void SetDirection(bool right);
	/// ���������� �������� ��ġ�� �ʱ�ȭ���ִ� �Լ�
	void BeginMove(const Vector2& to, float delay);
	// ������ ����
	virtual const AnimationSequence* GetSequenceByState(NPCState state) const = 0;
protected:
	// �̵� ������
	Vector2								_startPos;           
	// ��ǥ ��ġ
	Vector2								_targetPos;           
	//npc�̵��ӵ�
	float								_moveSpeed = 50.0f;
	// �̵� ��� �ð�
	float								_elapsed = 0.0f;     
	// ��ǥ������ ��ü �Ÿ�
	float								_totalDistance = 0.0f;
	//�ִϸ��̼��� �¿��Ǵ�
	bool								_facingRight = true; 
	//fsm�� ���� ���º����뵵�θ���
	NPCState							_state = NPCState::IDLE;
	//�ִϸ��̼��� ������ ����� ������
	std::unique_ptr<Animator>			_animator;
	//�������� ����
	bool _moving = false;
	// ���� �ȱ� ���� ����
	bool _moveStarted = false;
	//������Ÿ��
	float _delayTime = 0.0f;
	
};
	
