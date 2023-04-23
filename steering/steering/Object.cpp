#include "stdafx.h"
#include "Object.h"

/*ステアの計算をするためのオブジェクトクラス
各タイヤの向きと速さのベクトルを入力すればベクトルの計算をして表示してくれるようにする*/
Vec2 pos = {400,300};
Vec2 size = { 200,200 };
RectF Robot{pos,size};
RectF LF_frame;
RectF RF_frame;
RectF RB_frame;
RectF LB_frame;

Object &Object::draw(Color Framecolor=Palette::White) {
	Robot.setCenter(400,300).drawFrame(0, 1, Framecolor);
	/*ロボットの外枠*/
	LF_frame.set( Robot.pos,size / 3 ).drawFrame(0, 1, Framecolor);
	/*ロボットの左上*/
	RF_frame.set(Robot.tr().x - size.x / 3, Robot.pos.y, size / 3).drawFrame(0, 1, Framecolor);
	/*右上*/
	LB_frame.set(Robot.bl().x, Robot.bl().y - size.y / 3, size / 3).drawFrame(0, 1, Framecolor);
	/*左下*/
	RB_frame.set(Robot.br() - size / 3, size / 3).drawFrame(0, 1, Framecolor);
	/*右下*/
	return *this;
}

Object& Object::SetLF(Vec2 r) {
	Circle{ { r.x + Robot.tl().x,-r.y + Robot.tl().y },10 }.draw();
	//Shape2D::Arrow(Robot.tl(), { r.x + Robot.tl().x,-r.y + Robot.tl().y }, 5, Vec2{ 5,5 }).draw();
	return *this;
}
Object& Object::SetLB(Vec2 r) {
	Circle{ { r.x + Robot.bl().x,-r.y + Robot.bl().y },10 }.draw();
	//Shape2D::Arrow(Robot.bl(), { r.x + Robot.bl().x,-r.y + Robot.bl().y }, 5, Vec2{ 5,5 }).draw();
	return *this;
}
Object& Object::SetRF(Vec2 r) {
	Circle{ { r.x + Robot.tr().x,-r.y + Robot.tr().y },10 }.draw();
	//Shape2D::Arrow(Robot.tr(), { r.x + Robot.tr().x,-r.y + Robot.tr().y }, 5, Vec2{ 5,5 }).draw();
	return *this;
}
Object& Object::SetRB(Vec2 r) {
	Circle{ { r.x + Robot.br().x,-r.y + Robot.br().y },10 }.draw();
	//Shape2D::Arrow(Robot.br(), { r.x + Robot.br().x,-r.y + Robot.br().y }, 5, Vec2{ 5,5 }).draw();
	return *this;
}



Object& Object::SetLF(double length,double angle) {
	//Circle{LF_frame.center(),}.draw();
	//Shape2D::Arrow(Robot.tl(), { r.x + Robot.tl().x,-r.y + Robot.tl().y }, 5, Vec2{ 5,5 }).draw();
	return *this;
}
Object& Object::SetLB(double length, double angle) {
	//Circle{ { r.x + Robot.bl().x,-r.y + Robot.bl().y },10 }.draw();
	//Shape2D::Arrow(Robot.bl(), { r.x + Robot.bl().x,-r.y + Robot.bl().y }, 5, Vec2{ 5,5 }).draw();
	return *this;
}
Object& Object::SetRF(double length, double angle) {
	//Circle{ { r.x + Robot.tr().x,-r.y + Robot.tr().y },10 }.draw();
	//Shape2D::Arrow(Robot.tr(), { r.x + Robot.tr().x,-r.y + Robot.tr().y }, 5, Vec2{ 5,5 }).draw();
	return *this;
}
Object& Object::SetRB(double length, double angle) {
	//Circle{ { r.x + Robot.br().x,-r.y + Robot.br().y },10 }.draw();
	//Shape2D::Arrow(Robot.br(), { r.x + Robot.br().x,-r.y + Robot.br().y }, 5, Vec2{ 5,5 }).draw();
	return *this;
}

