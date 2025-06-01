#include "DrawCommand.h"
#include "framework.h"
using namespace Gdiplus;

// ��ü �̹��� or �ܼ� ��ġ ������
DrawImageCommand::DrawImageCommand(Image* img, int dstX, int dstY, int width, int height)
    : _img(img), _x(dstX), _y(dstY), _w(width), _h(height),
    _srcX(0), _srcY(0), _useSrcRect(false) {
}

// ��������Ʈ ��Ʈ �ڸ����
DrawImageCommand::DrawImageCommand(Image* img, int dstX, int dstY, int srcX, int srcY, int width, int height)
    : _img(img), _x(dstX), _y(dstY), _srcX(srcX), _srcY(srcY), _w(width), _h(height),
    _useSrcRect(true) {
}
// ���շ��̾� ������
//DrawImageCommand::DrawImageCommand(Image* img, int dstX, int dstY, int offsetX, int offsetY, int width, int height)
//    : _img(img), _x(dstX), _y(dstY), _offsetX(offsetX), _offsetY(offsetY), _w(width), _h(height),
//    _useSrcRect(false) {
//}

void DrawImageCommand::Execute(Graphics* g, float sx, float sy)
{
    if (!_img) return;

    if (_useSrcRect)
    {
        g->DrawImage(
            _img,
            static_cast<INT>(_x * sx), static_cast<INT>(_y * sy),  // ȭ�鿡 �׸� ��ġ
            _srcX, _srcY,                                           // �̹��� �� �ڸ� ��ġ
            _w, _h,                                                 // �ڸ� ũ��
            UnitPixel
        );
    }
    else
    {
        g->DrawImage(
            _img,
            static_cast<INT>(_x * sx),
            static_cast<INT>(_y * sy),
            static_cast<INT>(_w * sx),
            static_cast<INT>(_h * sy)
        );
    }
}
