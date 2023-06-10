# include <Siv3D.hpp> // OpenSiv3D v0.6.8
# include "Steer.h"
# include "Object.h"

#include <udon/types/Vector2D.hpp>

#include <udon/com/pad/PadPS5.hpp>
#include <udon/siv3d/SivPadPS5.hpp>

void Main()
{
	udon::PadPS5<udon::SivPadPS5> pad{ { 0 } };

	Color color =Palette::White;
	Steer steer;
	Object robot;

	Vec2 LeftAxis{0,0};
	double InputTurn = 0;

	bool stopped = true;
	for (const auto& info : System::EnumerateGamepads())
	{
		Print << U"[{}] {} ({:#x} {:#x})"_fmt(info.playerIndex, info.name, info.vendorID, info.productID);
	}
	while (System::Update())
	{
		ClearPrint();
		pad.update();
		if (pad)
		{
			const auto data = pad.getStick();
			LeftAxis = data.vector;
			InputTurn = data.turn;

			//if (const auto gamepad=Gamepad(1)) {
			//	/*ps5だったらGamepad(0)だよ*/
			//	/*ps4だったらGamepad(1)だよ*/
			//	//const auto& info = gamepad.getInfo();
			//	LeftAxis.x = (int)(gamepad.axes.at(0)*255);
			//	LeftAxis.y = -(int)(gamepad.axes.at(1)*255);
			//	InputTurn = (int)(gamepad.axes.at(3)*255);
			//	/*ps5だったらat(2)だよ*/
			//	/*ps4だったらat(3)だよ*/

			//	Print << LeftAxis <<U" "<< InputTurn;
			//}

			//LeftAxis.y = KeyW.pressed()*40 - KeyS.pressed()*40;
			//LeftAxis.x = KeyD.pressed()*40 - KeyA.pressed()*40;
			//InputTurn = KeyRight.pressed()*40 - KeyLeft.pressed()*40;

			Print << Scene::DeltaTime() * 1000;
			SimpleGUI::CheckBox(stopped, U"非常停止", {110,50});
			steer.Update({ LeftAxis.x,-LeftAxis.y }, InputTurn, 0);
			//steer.Show();
			if (stopped) {
				steer.Stop();
			}
			else {
				steer.Allow();
			}
			Print<<steer.GetPower(place::LF);
			std::array<double, 4>length = { steer.GetPower(place::LF).y
				,steer.GetPower(place::RF).y ,steer.GetPower(place::RB).y ,steer.GetPower(place::LB).y};
			std::array<double, 4>angle = { steer.GetPower(place::LF).x ,steer.GetPower(place::RF).x ,steer.GetPower(place::RB).x ,steer.GetPower(place::LB).x };

			robot.SetPower(length, angle).draw(color);
		}
	}
}
