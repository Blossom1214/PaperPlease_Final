#pragma once
#include <memory>
#include "framework.h"
#include <functional>
#include <vector>
#include <unordered_map>
#include "PMath.h"
enum class PlaybackType
{
	LOOP,
	ONCE,
	PINGPONG
};
//����UI�뵵
struct Parts
{
	std::wstring path;
	Vector2 offset;
	int zOrder;
	std::unique_ptr<Gdiplus::Image> img = nullptr;

	Parts() = default;
	Parts(Parts&&) = default;
	Parts& operator=(Parts&&) = default;

	Parts(const Parts&) = delete;
	Parts& operator=(const Parts&) = delete;
};
struct Frame {
	RECT rect{};
	float duration =0.1f;
	
};
struct AnimationSequence {
	std::vector<Frame> frames;
	PlaybackType playback = PlaybackType::LOOP; // �⺻�� ����
};
struct ImageResource
{
	//��¥�̹����� ���
	std::unique_ptr<Gdiplus::Image> img;
	//�ִϸ��̼��� ��ε�...(Ű�� idle�����Ű� �ִϸ��̼ǽ������� ���ͷεα�)
	std::unordered_map<std::wstring, AnimationSequence> animations;
	//�������� ������ �Ǿ��մ� ui������� �̷������� ����ؾ��ҵ�?//ex)���� ����� ����
	std::unordered_map<std::wstring, Parts> parts;

	POINT pos{ 0,0 };//x,y��ġ
	float scaleX = 1.0f;//������
	float scaleY = 1.0f;

	SIZE originalResolution{ 1280, 720 };//�����ػ�


	bool operator==(const ImageResource& other) const {
		return img.get() == other.img.get() &&
			pos.x == other.pos.x &&
			pos.y == other.pos.y &&
			scaleX == other.scaleX &&
			scaleY == other.scaleY &&
			originalResolution.cx == other.originalResolution.cx &&
			originalResolution.cy == other.originalResolution.cy&&
			parts.size() == other.parts.size();

	}
};
namespace std {//�ؽ����̺���� ���� ������ ����... ���ø�Ư��ȭ�� �߰���...
	template<>
	struct hash<ImageResource> {
		size_t operator()(const ImageResource& p) const noexcept
		{
			size_t h1 = hash<void*>()(p.img.get());
			size_t h2 = hash<int>()(p.pos.x ^ p.pos.y);
			size_t h3 = hash<float>()(p.scaleX);
			size_t h4 = hash<float>()(p.scaleY);
			size_t h5 = hash<int>()(p.originalResolution.cx ^ p.originalResolution.cy);
			size_t h6 = hash<size_t>()(p.parts.size());
			return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3) ^ (h5 << 4) ^ (h6 << 5);
		}
	};
}