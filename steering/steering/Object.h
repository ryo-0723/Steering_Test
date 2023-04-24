#pragma once
class Object
{
private:
	Vec2 pos  = { 400,300 };
	Vec2 size = { 200,200 };
	RectF Robot{ pos,size };
	std::array<RectF, 4> Rectframe{};
	std::array<double, 4> old_angle{};
	std::array<uint64, 4> time{};
	Vec3 Robot_Vec={};
public:
	Object() = default;

	Object& draw(const Color& Framecolor);

	Object& SetPower(std::array<double, 4>length, std::array<double, 4>angle);

};

