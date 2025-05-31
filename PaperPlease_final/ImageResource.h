#pragma once
#include <memory>
#include "framework.h"
#include <functional>
#include <vector>
#include <unordered_map>
enum class PlaybackType
{
	LOOP,
	ONCE,
	PINGPONG
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
	std::unique_ptr<Gdiplus::Image> img; //��¥�̹����� ���
	
	std::unordered_map<std::wstring, AnimationSequence> animations;//�ִϸ��̼��� ��ε�...(Ű�� idle�����Ű� �ִϸ��̼ǽ������� ���ͷεα�)

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
			originalResolution.cy == other.originalResolution.cy;

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
			return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3) ^ (h5 << 4);
		}
	};
}