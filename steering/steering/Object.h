#pragma once
class Object
{
private:


public:

	Object(){}


	Object& draw(Color Framecolor);

	Object& SetLF(Vec2 r);

	Object& SetLB(Vec2 r);

	Object& SetRF(Vec2 r);

	Object& SetRB(Vec2 r);



	Object& SetLF(double length, double angle);

	Object& SetLB(double length, double angle);

	Object& SetRF(double length, double angle);

	Object& SetRB(double length, double angle);

};

