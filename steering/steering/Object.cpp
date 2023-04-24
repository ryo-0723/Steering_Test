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
	Robot.setCenter(400,300).moveBy(Robot_Vec.x,-Robot_Vec.y).rotatedAt(Robot.center(), Robot_Vec.z).drawFrame(0, 1, Framecolor);
	/*ロボットの外枠*/
	Line{Robot.tl().rotatedAt(Robot.center(), Robot_Vec.z),Robot.tr().rotatedAt(Robot.center(), Robot_Vec.z) }.draw(3, Palette::Red);

	Rectframe[0].set(Robot.pos, size / 3).rotatedAt(Robot.center(), Robot_Vec.z).drawFrame(0, 1, Framecolor);
	/*ロボットの左上*/
	Rectframe[1].set(Robot.tr().x - size.x / 3, Robot.pos.y, size / 3).rotatedAt(Robot.center(), Robot_Vec.z).drawFrame(0, 1, Framecolor);
	/*右上*/
	Rectframe[2].set(Robot.br() - size / 3, size / 3).rotatedAt(Robot.center(), Robot_Vec.z).drawFrame(0, 1, Framecolor);
	/*右下*/
	Rectframe[3].set(Robot.bl().x, Robot.bl().y - size.y / 3, size / 3).rotatedAt(Robot.center(), Robot_Vec.z).drawFrame(0, 1, Framecolor);
	/*左下*/
	return *this;
}

/*赤になっているほうが0°のとき前に向いていた方*/
Object& Object::SetPower(std::array<double,4>length, std::array<double,4>angle) {
	std::array<Vec2, 4>Vector{};
	for (int i = 0; i < 4; i++) {
		Vector[i] = { length[i] * sin(ToRadians(angle[i])) ,length[i] * cos(ToRadians(angle[i])) };
		RectF{ 0,0,Rectframe[i].w / 3.1,Rectframe[i].h / 1.5 }.setCenter(Rectframe[i].center()).rotated(ToRadians(angle[i]))
			.rotatedAt(Robot.center(), Robot_Vec.z)
			.draw(Palette::Red, Palette::Red, Palette::White, Palette::White);
		Shape2D::Arrow(Rectframe[i].center().rotatedAt(Robot.center(), Robot_Vec.z)
			, { Rectframe[i].center().rotatedAt(Robot.center(), Robot_Vec.z).x + Vector[i].rotated(-Robot_Vec.z).x
			, Rectframe[i].center().rotatedAt(Robot.center(), Robot_Vec.z).y - Vector[i].rotated(-Robot_Vec.z).y }
			, 6
			, Vec2{ 8,8 }).draw();

		if (fliped_jadge(old_angle[i], angle[i])) {
			time[i] = Time::GetMillisec();
		}
		if (Time::GetMillisec() - time[i] < 200) {
			Rectframe[i].rotatedAt(Robot.center(), Robot_Vec.z).drawFrame(0, 3, Palette::Orange);
		}
		old_angle[i] = angle[i];

		int8_t xangle = i == 2 || i == 3 ? -1 : 1;
		int8_t yangle = i == 1 || i == 2 ? -1 : 1;
		Robot_Vec.z += (/*ｘ軸*/xangle*(Vector[i].x * cos(0.25 * Math::Pi))
			+/*ｙ軸*/yangle * (Vector[i].y * cos(-0.25 * Math::Pi))) / 9000;
		Robot_Vec.x += Vector[i].rotated( -Robot_Vec.z).x / 60;
		Robot_Vec.y += Vector[i].rotated( -Robot_Vec.z).y / 60;
	}
	return *this;
}
