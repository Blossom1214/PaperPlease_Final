#pragma once
enum class StampMode
{
	NONE,
	APPROVE,
	DENY
};
class Stemp
{
public:
	Stemp() = default;
	virtual ~Stemp() = default;
private:
	
	StampMode mode = StampMode::NONE;
};

