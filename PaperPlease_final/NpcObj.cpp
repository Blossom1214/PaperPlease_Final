#include "NpcObj.h"
using namespace std;
bool NpcObj::MoveTowardsTarget(float dt)
{
    //��ǥ������ �Ÿ��� 0�̸��� �̹� �ش���ġ�� �ִ°�
    if (_totalDistance <= 0.0f)
    {
        //�ش���ġ�� �ִ°��̴� �ش���ġ�� �����ǿ� ����
        _position = _targetPos;
        return true;    
    }
    //�ð���ŭ ����(����ð�)
    _elapsed += dt;
    if (!_moveStarted && _elapsed >= _delayTime)
    {
        _elapsed = 0.0f;                   
        _moveStarted = true;               
    }
    if (!_moveStarted)
        return false;
    //�ӵ��� �ð��� ���Ͽ��� ������� �̵��� �Ÿ��� ���
    float traveled = _moveSpeed * _elapsed;
    //��ä���� ���� ������� ����Ͽ� ������ �ּҰ��� 0���� �ִ밪�� 1 �� 1�� �Ѿ���ʰ� ����ִ� ��������
    float t = clamp(traveled / _totalDistance, 0.0f, 1.0f);
    //������ġ�κ����� ��Ÿ����ġ������ ���������� ���� �������� �����
    _position = _startPos.Lerp(_targetPos, t);
    //���� b-a���Ͽ����� x�ǰ��� 0���� ũ�ų� ������ ����������!
    SetDirection((_targetPos - _startPos).x >= 0.0f);
    //�� �������� ������� 1�� �����ϰų� �Ѿ�� ��(��� 1�̵Ǹ� �����Ѱ�)
    return(t >= 1.0f);

}
void NpcObj::BeginMove(const Vector2& to,float delay)
{
    //�������������� ��ġ������ ������ġ�� �ʱ�ȭ ���ִ��Լ�
    _startPos = _position;
    _targetPos = to;
    _elapsed = 0.0f;
    _delayTime = delay;
    _moveStarted = false;
    _totalDistance = (_targetPos - _startPos).Length();
    _moving = true;
}
void NpcObj::SetState(NPCState state)
{
    _state = state;

    const AnimationSequence* seq = GetSequenceByState(state);
    if (seq)
    {
        _animator->SetSequence(seq);
        _animator->Play();
    }
}

void NpcObj::SetDirection(bool right)
{
    _facingRight = right;
}