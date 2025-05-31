#pragma once
#include "IPlaybackPolicy.h"
class PingPongPolicy : public IPlaybackPolicy
{
public:
	void AdvanceFrame(int& frameIndex, int sequenceSize, float& elapsedTime, bool& playing)override
	{
		if (sequenceSize <= 1) //�ִϸ��̼ǽ���������� 1�����ų� �۴ٸ� �ִϸ��̼� �������� �Ѱ��ΰ��̹Ƿ� �׳� ����..
			return;
		if (_forward)//�����̶��?
		{
			frameIndex++;//��ĭ �ε����� �ø���
			if (frameIndex >= sequenceSize)//������������� �������ų� �ε����� ��ũ�ٴ°��� �� �ִϸ��̼��������� ���� �ٴٶ����� �˼�����
			{
				frameIndex = sequenceSize - 2;//�� �װ�쿡�� ������ ���� �ش��ϴ� �ε������� 2�� ���� ���簪 -1 ���°��Ǳ⶧���� �������·� ���ư������ְ�
				_forward = false;//���� �̰��� false�� �ٲۻ��¿��� �ٽ� �̰��� �ݺ����ȿ��ֱ⶧���� �ٽ� ����

			}


		}
		else
		{
			frameIndex--; //���乹..�Ųٷ� ���ư��°���..
			if (frameIndex < 0)
			{
				frameIndex = 1;
				_forward = true;

			}
		}

	}
private:
	bool _forward = true;
};