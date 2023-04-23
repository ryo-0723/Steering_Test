#include "stdafx.h"
#include "Object.h"

/*ステアの計算をするためのオブジェクトクラス
各タイヤの向きと速さのベクトルを入力すればベクトルの計算をして表示してくれる*/

/// @brief タイヤが360一気に回転したかを判定する
/// @param before 前周期の角度
/// @param after 今週期の角度
/// @return 反転したらtrueを返す
bool  fliped_jadge(double before, double after) {
	bool flag;
	if (abs(before - after) > 300) {
		flag = true;
	}
	else {
		flag = false;
	}
	return flag;
}

Object& Object::draw(const Color& Framecolor=Palette::White) {
	Robot.setCenter(400,300).moveBy(Robot_Vec.x,-Robot_Vec.y).rotated(Robot_Vec.z).drawFrame(0, 1, Framecolor);
	/*ロボットの外枠*/
	//LF_frame.set( Robot.pos,size / 3 ).drawFrame(0, 1, Framecolor);
	///*ロボットの左上*/
	//RF_frame.set(Robot.tr().x - size.x / 3, Robot.pos.y, size / 3).drawFrame(0, 1, Framecolor);
	///*右上*/
	//LB_frame.set(Robot.bl().x, Robot.bl().y - size.y / 3, size / 3).drawFrame(0, 1, Framecolor);
	///*左下*/
	//RB_frame.set(Robot.br() - size / 3, size / 3).drawFrame(0, 1, Framecolor);
	///*右下*/

	Rectframe[0].set(Robot.pos, size / 3).drawFrame(0, 1, Framecolor);
	/*ロボットの左上*/
	Rectframe[1].set(Robot.tr().x - size.x / 3, Robot.pos.y, size / 3).drawFrame(0, 1, Framecolor);
	/*右上*/
	Rectframe[2].set(Robot.br() - size / 3, size / 3).drawFrame(0, 1, Framecolor);
	/*右下*/
	Rectframe[3].set(Robot.bl().x, Robot.bl().y - size.y / 3, size / 3).drawFrame(0, 1, Framecolor);
	/*左下*/
	return *this;
}
//
//Object& Object::SetLF(Vec2 r) {
//	Circle{ LF_frame.center().x + r.x, LF_frame.center().y - r.y ,7 }.draw();
//	//Shape2D::Arrow(LF_frame.center(), { LF_frame.center().x + r.x, LF_frame.center().y - r.y }, 5, Vec2{ 5,5 }).draw();
//	return *this;
//}
//Object& Object::SetRF(Vec2 r) {
//	Circle{ RF_frame.center().x + r.x, RF_frame.center().y - r.y ,7 }.draw();
//	//Shape2D::Arrow(RF_frame.center(), { RF_frame.center().x + r.x, RF_frame.center().y - r.y }, 5, Vec2{ 5,5 }).draw();
//	return *this;
//}
//Object& Object::SetRB(Vec2 r) {
//	Circle{ RB_frame.center().x + r.x, RB_frame.center().y - r.y ,7 }.draw();
//	//Shape2D::Arrow(RB_frame.center(), { RB_frame.center().x + r.x, RB_frame.center().y - r.y }, 5, Vec2{ 5,5 }).draw();
//	return *this;
//}
//Object& Object::SetLB(Vec2 r) {
//	Circle{ LB_frame.center().x + r.x, LB_frame.center().y - r.y ,7 }.draw();
//	//Shape2D::Arrow(LB_frame.center(), { LB_frame.center().x + r.x, LB_frame.center().y - r.y }, 5, Vec2{ 5,5 }).draw();
//	return *this;
//}



/*赤になっているほうが0°のとき前に向いていた方*/
Object& Object::SetPower(std::array<double,4>length, std::array<double,4>angle) {
	std::array<Vec2, 4>Vector{};
	for (int i = 0; i < 4; i++) {
		Vector[i] = { length[i] * sin(ToRadians(angle[i])) ,length[i] * cos(ToRadians(angle[i])) };
		RectF{ 0,0,Rectframe[i].w / 3.1,Rectframe[i].h / 1.5 }.setCenter(Rectframe[i].center()).rotated(ToRadians(angle[i]))
			.draw(Palette::Red, Palette::Red, Palette::White, Palette::White);
		Shape2D::Arrow(Rectframe[i].center()
			, { Rectframe[i].center().x + Vector[i].x
			, Rectframe[i].center().y - Vector[i].y }
			, 6
			, Vec2{ 8,8 }).draw();

		if (fliped_jadge(old_angle[i], angle[i])) {
			time[i] = Time::GetMillisec();
		}
		if (Time::GetMillisec() - time[i] < 200) {
			Rectframe[i].drawFrame(0, 3, Palette::Orange);
		}
		old_angle[i] = angle[i];
	}
	for (int i = 0; i < 4;i++) {
		/*回転ベクトル以外のベクトルを求める*/
		Robot_Vec.x += Vector[i].x/100;
		Robot_Vec.y += Vector[i].y/100;
		Robot_Vec.z += Vec2{ 0,Vector[i].y }.rotate((i * -0.5 - 0.25) * Math::Pi).x;
	}
	return *this;
}
//Object& Object::SetLF(double length,double angle) {
//	RectF{ 0,0,LF_frame.w / 3.1,LF_frame.h / 1.5 }.setCenter(LF_frame.center()).rotated(ToRadians(angle))
//		.draw(Palette::Red, Palette::Red, Palette::White, Palette::White);
//	Shape2D::Arrow(LF_frame.center()
//			, { LF_frame.center().x+length * sin(ToRadians(angle))
//			, LF_frame.center().y - length * cos(ToRadians(angle)) }
//			, 6
//			, Vec2{ 8,8 }).draw();
//
//	if (fliped_jadge(old_angle[0], angle)) {
//		time[0] = Time::GetMillisec();
//	}
//	if (Time::GetMillisec()-time[0]<200) {
//		LF_frame.drawFrame(0, 3,Palette::Orange);
//	}
//	old_angle[0] = angle;
//	return *this;
//}
//Object& Object::SetRF(double length, double angle) {
//	RectF{ 0,0,RF_frame.w / 3.1,RF_frame.h / 1.5 }.setCenter(RF_frame.center()).rotated(ToRadians(angle))
//		.draw(Palette::Red, Palette::Red, Palette::White, Palette::White);
//	Shape2D::Arrow(RF_frame.center()
//		, { RF_frame.center().x + length * sin(ToRadians(angle))
//		, RF_frame.center().y - length * cos(ToRadians(angle)) }
//		, 6
//		, Vec2{ 8,8 }).draw();
//
//	if (fliped_jadge(old_angle[1], angle)) {
//		time[1] = Time::GetMillisec();
//	}
//	if (Time::GetMillisec() - time[1] < 200) {
//		RF_frame.drawFrame(0, 3, Palette::Orange);
//	}
//	old_angle[1] = angle;
//	return *this;
//}
//Object& Object::SetRB(double length, double angle) {
//	RectF{ 0,0,RB_frame.w / 3.1,RB_frame.h / 1.5 }.setCenter(RB_frame.center()).rotated(ToRadians(angle))
//		.draw(Palette::Red, Palette::Red, Palette::White, Palette::White);
//	Shape2D::Arrow(RB_frame.center()
//		, { RB_frame.center().x + length * sin(ToRadians(angle))
//		, RB_frame.center().y - length * cos(ToRadians(angle)) }
//		, 6
//		, Vec2{ 8,8 }).draw();
//
//	if (fliped_jadge(old_angle[2], angle)) {
//		time[2] = Time::GetMillisec();
//	}
//	if (Time::GetMillisec() - time[2] < 200) {
//		RB_frame.drawFrame(0, 3, Palette::Orange);
//	}
//	old_angle[2] = angle;
//	return *this;
//}
//Object& Object::SetLB(double length, double angle) {
//	RectF{ 0,0,LB_frame.w / 3.1,LB_frame.h / 1.5 }.setCenter(LB_frame.center()).rotated(ToRadians(angle))
//		.draw(Palette::Red, Palette::Red, Palette::White, Palette::White);
//	Shape2D::Arrow(LB_frame.center()
//			, { LB_frame.center().x + length * sin(ToRadians(angle))
//			, LB_frame.center().y - length * cos(ToRadians(angle)) }
//			, 6
//			, Vec2{ 8,8 }).draw();
//
//	if (fliped_jadge(old_angle[3], angle)) {
//		time[3] = Time::GetMillisec();
//	}
//	if (Time::GetMillisec() - time[3] < 200) {
//		LB_frame.drawFrame(0, 3, Palette::Orange);
//	}
//	old_angle[3] = angle;
//	return *this;
//}


