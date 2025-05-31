#include "UIStempBar.h"
void UIStempBar::Init()
{
	_pos = { 1280,400 };

}
void UIStempBar::Update(float dt)
{
	

}
void UIStempBar::Render()
{


}
void UIStempBar::ClickKey()
{
	_StempOn = true;
	_pos = { _pos.x - 200,_pos.y };

}
void UIStempBar::Release()
{


}