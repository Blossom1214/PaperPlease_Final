#pragma once
#include "Collision.h"
class Stemp
{
public:
	virtual ~Stemp() = default;
	virtual void Update(float dt) = 0;
	virtual void Render(Gdiplus::Graphics* g) = 0;

	void SetPos(const Vector2& pos) { _pos = pos; _collisionStemp->SetPos(pos); }
	void SetTarget(RectCollision* approve, RectCollision* deny) {
		_approveTarget = approve;
		_denyTarget = deny;
	}
protected:
	Vector2 _pos;
	std::unique_ptr<RectCollision> _collisionStemp;
	RectCollision* _approveTarget = nullptr;
	RectCollision* _denyTarget = nullptr;
};

class APPROVE_Stemp : public Stemp
{
public:
	void Update(float dt)override;
	void Render(Gdiplus::Graphics* g)override;


};

class DENY_Stemp : public Stemp
{



};