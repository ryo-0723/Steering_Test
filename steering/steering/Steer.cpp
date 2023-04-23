#include "stdafx.h"
#include "Steer.h"

/*ベクトルの計算後のデータ保存場所*/
struct Wheel {
	double length, angle, oldangle, offset;

	/// @brief -double--+doubleの範囲に変更する関数
	void  update() {
		/*nanのままいったん計算*/
		/*無限増加を防ぐために違う変数を作る*/
		double overangle = angle + 180.00;
		double oldoverangle = oldangle + 180.00;

		/*nanとの比較演算子は常にfalseが出るらしい*/
		/*nan判定の前に行うことでバグはなくなるのでは？*/
		if (oldoverangle - overangle > 330 && oldoverangle - overangle <= 360) 
			/*変化量がほぼ一周分になるときは一周したと判定する*/
			offset += 360;
		if (oldoverangle - overangle < -330 && oldoverangle - overangle >= -360) 
			/*変化量がほぼ一周分になるときは一周したと判定する*/
			offset -= 360;

		/*nanをなくす*/
		if (IsNaN(angle))/*角度がnanのときは前周期の角度のままにする*/
			angle = oldangle;

		/*最初はタイヤの回転角度は0から359までの範囲にする*/
		/*最大の許容値を400としておいて、回転量が少ないときは小さく回転し、回転量が多いときにタイヤを反転して許容値から離す*/
		if (getangle() >= 350) {
			if (getangle() > 400)/*絶対反転角---個の角度になったときは必ず反転をする*/
				offset -= 360.00;
			if (angle - oldangle > 20)/*指定量より動く回転の量が多いときタイヤをあるときのみ360回転させる*/
				offset -= 360.00;
		}
		if (getangle() <= 10) {
			if (getangle() < -40) /*絶対反転角---個の角度になったときは必ず反転をする*/
				offset += 360.00;
			if (angle - oldangle < -20)/*指定量より動く回転の量が多いときタイヤをあるときのみ360回転させる*/
				offset += 360.00;
		}
	}
	/// @brief 前周期のデータを更新する
	void end_update() {
		oldangle = angle;
	}
	double getangle() {
		return angle + offset;
	}
	double getoldangle() {
		return oldangle + offset;
	}
};

std::array<Wheel, 4> Tire;
/*角度と大きさを保存する*/
Vec2 LF, LB, RF, RB;
void Steer::Update(Vec2 Axis, int z, double gyro) {
	/*とりあえずジャイロのことは加味せずに計算していく*/
	/*z（旋回のベクトル）を(0,z)とすることでy軸と同じ方向になるベクトルが作れる*/
	//LF--時計回り
	std::array<Vec2, 4> data;
	for (int i = 0; i < 4; i++) {
		data[i] = Axis + Vec2{ 0,z }.rotate((i * -0.5 - 0.25) * Math::Pi);/*Vec2*/
	}
	LF = data[0];
	RF = data[1];
	RB = data[2];
	LB = data[3];

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

Vec2 Steer::GetLF() {
	return LF;
}
Vec2 Steer::GetRF() {
	return RF;
}
Vec2 Steer::GetRB() {
	return RB;
}
Vec2 Steer::GetLB() {
	return LB;
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

