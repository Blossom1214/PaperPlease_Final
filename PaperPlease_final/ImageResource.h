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
//파츠UI용도
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
	PlaybackType playback = PlaybackType::LOOP; // 기본은 루프
};
struct ImageResource
{
	//진짜이미지의 경로
	std::unique_ptr<Gdiplus::Image> img;
	//애니메이션의 경로들...(키는 idle같은거고 애니메이션시퀀스는 벡터로두기)
	std::unordered_map<std::wstring, AnimationSequence> animations;
	//복합적인 구조로 되어잇는 ui같은경우 이런식으로 사용해야할듯?//ex)여권 도장바 등등등
	std::unordered_map<std::wstring, Parts> parts;

	POINT pos{ 0,0 };//x,y위치
	float scaleX = 1.0f;//스케일
	float scaleY = 1.0f;

	SIZE originalResolution{ 1280, 720 };//기준해상도


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
namespace std {//해시테이블덕에 정말 개같이 만듬... 템플릿특수화로 추가함...
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