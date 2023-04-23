#include "stdafx.h"
#include "Steer.h"

void Steer::Update(Vec2 Axis, double z, double gyro) {
	/*とりあえずジャイロのことは加味せずに計算していく*/
	/*z（旋回のベクトル）を(0,z)とすることでy軸と同じ方向になるベクトルが作れる*/
	//LF--時計回り
	std::array<Vec2, 4> data{};
	for (int i = 0; i < 4; i++) {
		data[i] = Axis + Vec2{ 0,z }.rotate((i * -0.5 - 0.25) * Math::Pi);/*Vec2*/
	}
	for (int i = 0; i < 4; i++) {
		Tire[i].length = data[i].length();
		//Tire[i].angle = ToDegrees(data[i].yx().rotate(-0.5 * Math::Pi).getAngle());
		Tire[i].angle = ToDegrees(data[i].yx().rotated(-0.5 * Math::Pi).getAngle());	/*overangleの時用*/
		Tire[i].update();
		}

	const auto max = (*std::max_element(Tire.begin(), Tire.end(), [](const Wheel& lhs, const Wheel& rhs) {
		return lhs.length < rhs.length;})).length;
	/*PWMの最大値をとる*/
	int MAX = 100;
	if (max > MAX) {
		double maximum = MAX / max;
		for (int i = 0; i < 4; i++) {
			Tire[i].length *= maximum;
		}
	}

	for (int i = 0; i < 4; i++) {
		Print << U" angle: " << Tire[i].angle		<< U" length: " << Tire[i].length;
		Print << U" overa: " << Tire[i].getangle() << U" offset: " << Tire[i].offset;
		Tire[i].end_update();
	}
	Print << Tire[0].oldangle;

}

void Steer::show() {


}

void Steer::Stop() {


}

double Steer::GetLF_l() {
	return Tire[0].length;
}
double Steer::GetLF_a() {
	return Tire[0].getangle();
}
double Steer::GetRF_l() {
	return Tire[1].length;
}
double Steer::GetRF_a() {
	return Tire[1].getangle();
}
double Steer::GetRB_l() {
	return Tire[2].length;
}
double Steer::GetRB_a() {
	return Tire[2].getangle();
}
double Steer::GetLB_l() {
	return Tire[3].length;
}
double Steer::GetLB_a() {
	return Tire[3].getangle();
}

