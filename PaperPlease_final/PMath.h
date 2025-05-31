#pragma once
#include <cmath>
#include <algorithm>

struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;

	Vector2() = default;
	Vector2(float _x, float _y) : x(_x), y(_y) {}
	/// ���� ����
	Vector2 operator+(const Vector2& other) const { return { x + other.x, y + other.y }; }
	/// ���� ����
	Vector2 operator-(const Vector2& other) const { return { x - other.x, y - other.y }; }
	/// ��Į�� ��
	Vector2 operator*(float scalar) const { return { x * scalar, y * scalar }; }
	/// ��Į�� ������
	Vector2 operator/(float scalar) const { return { x / scalar, y / scalar }; }
	/// ������ ��������
	Vector2& operator+=(const Vector2& other)
	{
		x += other.x; y += other.y; return *this;
	}
	/// ������ ��������
	Vector2& operator-=(const Vector2& other) {
		x -= other.x; y -= other.y; return *this;
	}
	/// ��Į�� ������
	Vector2& operator*=(float scalar) {
		x *= scalar; y *= scalar; return *this;
	}
	/// ��Į�� ����������
	Vector2& operator/=(float scalar) {
		x /= scalar; y /= scalar; return *this;
	}
	///�������� ������ �����ε�
	float& operator[](int index)
	{
		return index == 0 ? x : y;
	}
	///���� ���� ������(�б�����)
	const float& operator[](int index) const {
		return index == 0 ? x : y;
	}
	/// ������ ��ȣ����
	Vector2 operator-()const { return { -x,-y }; }
	/// �� ���Ͱ� ������ ��
	bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }
	/// �� ���Ͱ� �ٸ��� true
	bool operator!=(const Vector2& other) const { return !(*this == other); }
	/// (0, 0) ���� ��ȯ
	static Vector2 Zero() { return { 0.0f, 0.0f }; }
	/// (1, 1) ���� ��ȯ
	static Vector2 One() { return { 1.0f, 1.0f }; }
	/// X�� ���� ���� ��ȯ
	static Vector2 UnitX() { return { 1.0f, 0.0f }; }
	/// Y�� ���� ���� ��ȯ
	static Vector2 UnitY() { return { 0.0f, 1.0f }; }
	/// ���� �������� ���� ���� ���� (cos, sin)
	static Vector2 FromAngle(float radians) { return { std::cos(radians), std::sin(radians) }; }
	/// ������ ���� ��ȯ
	float Length() const { return std::sqrt(x * x + y * y); }
	/// ���� ������ ���� ��ȯ (��Ʈ ��� ����)
	float LengthSq() const { return x * x + y * y; }
	/// ������ ����ȭ�� ���纻 ��ȯ
	Vector2 Normalized() const 
	{
		float len = Length();
		return (len != 0) ? Vector2(x / len, y / len) : Vector2(0, 0);
	}
	/// ���� ���� ���
	float Dot(const Vector2& other) const { return x * other.x + y * other.y; }
	/// ���� ����: this���� target���� t��ŭ ���� (t �� [0,1])
	Vector2 Lerp(const Vector2& target, float t) const 
	{
		return (*this) + (target - *this) * t;
	}
	/// �� ���� ���� �Ÿ� ���
	float Distance(const Vector2& other) const { return (*this - other).Length(); }
	/// �Ÿ��� ���� ��ȯ (��Ʈ ����)
	float DistanceSq(const Vector2& other) const { return (*this - other).LengthSq(); }
	/// ������ ������ �������� ��ȯ (atan2)
	float Angle() const { return std::atan2(y, x); }
	/// �� ������ �־��� ���� ���� ������ ���� ��ȯ
	Vector2 Clamp(const Vector2& min, const Vector2& max) const
	{
		return { std::clamp(x, min.x, max.x), std::clamp(y, min.y, max.y) };
	}
	/// ������ ���� ���� ���� ��ȯ (90�� ȸ��)
	Vector2 Perpendicular() const { return { -y, x }; }
	/// �ٸ� ���� �������� ������ ���� ��ȯ
	Vector2 ProjectOnto(const Vector2& target) const 
	{
		Vector2 norm = target.Normalized();
		return norm * (this->Dot(norm));
	}
	/// �־��� ������ ���� �ݻ�� ���� ��ȯ
	Vector2 Reflect(const Vector2& normal) const
	{
		return *this - normal * (2.0f * this->Dot(normal));
	}
	/// ���� (2D�� ��� ��Į�� ��ȯ)
	float Cross(const Vector2& other) const { return x * other.y - y * other.x; }
	/// ���Һ� �� (Hadamard Product)
	Vector2 HadamardProduct(const Vector2& other) const
	{
		return { x * other.x, y * other.y };
	}
	/// �� ������ ���� ��ȯ
	Vector2 Abs() const { return { std::fabs(x), std::fabs(y) }; }
	/// �� ���и��� �� ū �� ����
	//Vector2 Max(const Vector2& other) const { return { std::max(x, other.x), std::max(y, other.y) }; }
	/// �� ���и��� �� ���� �� ����
	//Vector2 Min(const Vector2& other) const { return { std::min(x, other.x), std::min(y, other.y) }; }
	/// ���Ͱ� (0, 0)���� Ȯ��
	bool IsZero() const { return x == 0.0f && y == 0.0f; }
	/// x �Ǵ� y �� �ϳ��� NaN���� Ȯ��
	bool IsNaN() const { return std::isnan(x) || std::isnan(y); }
	/// (0, 0)�� �ſ� ������ �������� Ȯ�� (�ε��Ҽ� ������)
	bool IsNearlyZero(float epsilon = FLT_EPSILON) const
	{
		return std::fabs(x) < epsilon && std::fabs(y) < epsilon;
	}
	/// �� ���� ���� ���� ��ȯ (����)
	float AngleBetween(const Vector2& other) const
	{
		float dotProduct = this->Dot(other);
		float lengths = this->Length() * other.Length();
		if (lengths == 0.0f) return 0.0f;
		return std::acos(dotProduct / lengths);
	}
	/// ���͸� �־��� ���� ������ ȸ����Ų ��� ��ȯ
	Vector2 Rotate(float angle) const
	{
		float cosA = std::cos(angle);
		float sinA = std::sin(angle);
		return {
			x * cosA - y * sinA,
			x * sinA + y * cosA
		};
	}
	Vector2 Scale(const Vector2& other) const
	{
		return {
		x * other.x,
		y * other.y
		};
	}
	///�ִ���� ���� ����
	Vector2 Truncate(float maxLength) const
	{
		float len = Length();
		return (len > maxLength) ? this->Normalized() * maxLength : *this;
	}
	/// ���Ѵ�� �þ�� �� üũ(�ε��Ҽ��� �������)
	bool IsFinite() const
	{
		return std::isfinite(x) && std::isfinite(y);
	}
	/// �ڱ��ڽ��� ����ȭ �Ҷ� ���
	void Normalize() 
	{
		float len = Length();
		if (len != 0.0f) {
			x /= len;
			y /= len;
		}
	}
};