#pragma once
namespace Gdiplus {
    class Graphics;
    class Image;
}

class DrawCommand
{
public:
    virtual ~DrawCommand() = default;
    virtual void Execute(Gdiplus::Graphics* g, float sx, float sy) = 0;
};

class DrawImageCommand : public DrawCommand {
public:
    // ��ü �̹��� ������ ������
    DrawImageCommand(Gdiplus::Image* img, int dstX, int dstY, int width, int height);

    // ��������Ʈ ��Ʈ �ڸ���� ������
    DrawImageCommand(Gdiplus::Image* img, int dstX, int dstY, int srcX, int srcY, int width, int height);

    // ���շ��̾� ������
    //DrawImageCommand(Gdiplus::Image* img, int dstX, int dstY, int srcX, int srcY, int width, int height);



    void Execute(Gdiplus::Graphics* g, float sx, float sy) override;

private:
    Gdiplus::Image* _img;
    int _x, _y;         // ȭ�鿡 �׸� ��ġ
    int _w, _h;         // �׸� ũ�� or �ڸ� ũ��
    int _srcX, _srcY;   // �̹��� �� �ڸ� ��ġ
    //int _offsetX, _offsetY;//������ ��ġ
    bool _useSrcRect;   // �ڸ��� ����
};
//720 320