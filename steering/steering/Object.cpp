#include "stdafx.h"
#include "Object.h"

/*ステアの計算をするためのオブジェクトクラス
各タイヤの向きと速さのベクトルを入力すればベクトルの計算をして表示してくれる*/

Object& Object::draw(const Color& Framecolor=Palette::White) {
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
	Circle{ LF_frame.center().x + r.x, LF_frame.center().y - r.y ,7 }.draw();
	//Shape2D::Arrow(LF_frame.center(), { LF_frame.center().x + r.x, LF_frame.center().y - r.y }, 5, Vec2{ 5,5 }).draw();
	return *this;
}
Object& Object::SetLB(Vec2 r) {
	Circle{ LB_frame.center().x + r.x, LB_frame.center().y - r.y ,7 }.draw();
	//Shape2D::Arrow(LB_frame.center(), { LB_frame.center().x + r.x, LB_frame.center().y - r.y }, 5, Vec2{ 5,5 }).draw();
	return *this;
}
Object& Object::SetRF(Vec2 r) {
	Circle{ RF_frame.center().x + r.x, RF_frame.center().y - r.y ,7 }.draw();
	//Shape2D::Arrow(RF_frame.center(), { RF_frame.center().x + r.x, RF_frame.center().y - r.y }, 5, Vec2{ 5,5 }).draw();
	return *this;
}
Object& Object::SetRB(Vec2 r) {
	Circle{ RB_frame.center().x + r.x, RB_frame.center().y - r.y ,7 }.draw();
	//Shape2D::Arrow(RB_frame.center(), { RB_frame.center().x + r.x, RB_frame.center().y - r.y }, 5, Vec2{ 5,5 }).draw();
	return *this;
}



/*赤になっているほうが0°のとき前に向いていた方*/
Object& Object::SetLF(double length,double angle) {
	RectF{ 0,0,LF_frame.w / 3.1,LF_frame.h / 1.5 }.setCenter(LF_frame.center()).rotated(ToRadians(angle))
		.draw(Palette::Red, Palette::Red, Palette::White, Palette::White);
	Shape2D::Arrow(LF_frame.center()
			, { LF_frame.center().x+length * sin(ToRadians(angle))
			, LF_frame.center().y - length * cos(ToRadians(angle)) }
			, 6
			, Vec2{ 8,8 }).draw();
	return *this;
}
Object& Object::SetLB(double length, double angle) {
	RectF{ 0,0,LB_frame.w / 3.1,LB_frame.h / 1.5 }.setCenter(LB_frame.center()).rotated(ToRadians(angle))
		.draw(Palette::Red, Palette::Red, Palette::White, Palette::White);
	Shape2D::Arrow(LB_frame.center()
			, { LB_frame.center().x + length * sin(ToRadians(angle))
			, LB_frame.center().y - length * cos(ToRadians(angle)) }
			, 6
			, Vec2{ 8,8 }).draw();
	return *this;
}
Object& Object::SetRF(double length, double angle) {
	RectF{ 0,0,RF_frame.w / 3.1,RF_frame.h / 1.5 }.setCenter(RF_frame.center()).rotated(ToRadians(angle))
		.draw(Palette::Red, Palette::Red, Palette::White, Palette::White);
	Shape2D::Arrow(RF_frame.center()
		, { RF_frame.center().x + length * sin(ToRadians(angle))
		, RF_frame.center().y - length * cos(ToRadians(angle)) }
		, 6
		, Vec2{ 8,8 }).draw();
	return *this;
}
Object& Object::SetRB(double length, double angle) {
	RectF{ 0,0,RB_frame.w / 3.1,RB_frame.h / 1.5 }.setCenter(RB_frame.center()).rotated(ToRadians(angle))
		.draw(Palette::Red, Palette::Red, Palette::White, Palette::White);
	Shape2D::Arrow(RB_frame.center()
		, { RB_frame.center().x + length * sin(ToRadians(angle))
		, RB_frame.center().y - length * cos(ToRadians(angle)) }
		, 6
		, Vec2{ 8,8 }).draw();
	return *this;
}
