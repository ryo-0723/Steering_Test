#pragma once


class Steer
{
private:
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

	std::array<Wheel, 4> Tire{};
public:
	Steer() = default;

	void Update(Vec2 Axis, double z, double gyro);

	void Stop();

	void show();

	double GetLF_l();

	double GetLF_a();

	double GetRF_l();

	double GetRF_a();

	double GetRB_l();

	double GetRB_a();

	double GetLB_l();

	double GetLB_a();
};

