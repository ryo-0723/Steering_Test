#pragma once


class Steer
{
private:

public:
	Steer() {}

	void Update(Vec2 Axis, int z, double gyro);

	Vec2 GetLF();

	Vec2 GetLB();

	Vec2 GetRF();

	Vec2 GetRB();

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

