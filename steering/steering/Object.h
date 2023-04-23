#pragma once
class Object
{
private:
	Vec2 pos  = { 400,300 };
	Vec2 size = { 200,200 };
	RectF Robot{ pos,size };
	RectF LF_frame = {}, RF_frame = {}, RB_frame = {}, LB_frame = {};

public:
	Object() = default;

	Object& draw(const Color& Framecolor);

	Object& SetLF(Vec2 r);

	Object& SetLB(Vec2 r);

	Object& SetRF(Vec2 r);

	Object& SetRB(Vec2 r);



	Object& SetLF(double length, double angle);

	Object& SetLB(double length, double angle);

	Object& SetRF(double length, double angle);

	Object& SetRB(double length, double angle);

};

