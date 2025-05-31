#pragma once
#define NOMINMAX 
#include <Windows.h>
#include <memory>
#include <gdiplus.h>
class DoubleBufferManager
{
public:
	DoubleBufferManager();
	~DoubleBufferManager();

	void Initialize(HWND hwnd);
	void Resize(int width, int height);
	void Clear(const Gdiplus::Color& color = Gdiplus::Color(255, 0, 0, 0));
	Gdiplus::Graphics* GetGraphics(); // ����� �׷��� ��ü ����
	void Present(HWND hwnd);          // ȭ�鿡 ���
	void Release() { _backGraphics.reset(); _backBuffer.reset();}
private:
	std::unique_ptr<Gdiplus::Bitmap> _backBuffer;
	std::unique_ptr<Gdiplus::Graphics> _backGraphics;
	int _width=0;
	int _height=0;
};

