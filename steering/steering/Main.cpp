# include <Siv3D.hpp> // OpenSiv3D v0.6.8
# include "Steer.h"
# include "Object.h"
void Main()
{
	Color color =Palette::White;
	Steer steer;
	Object robot;

	Vec2 LeftAxis{0,0};
	double InputTurn = 0;

	for (const auto& info : System::EnumerateGamepads())
	{
		Print << U"[{}] {} ({:#x} {:#x})"_fmt(info.playerIndex, info.name, info.vendorID, info.productID);
	}
	while (System::Update())
	{
		ClearPrint();
		
		if (const auto gamepad=Gamepad(0)) {
			/*ps5だったらGamepad(0)だよ*/
			/*ps5だったらGamepad(1)だよ*/
			//const auto& info = gamepad.getInfo();
			LeftAxis.x = (int)(gamepad.axes.at(0)*255);
			LeftAxis.y = -(int)(gamepad.axes.at(1)*255);
			InputTurn = (int)(gamepad.axes.at(2)*255);
			/*ps5だったらat(2)だよ*/
			/*ps4だったらat(3)だよ*/

			Print << LeftAxis <<U" "<< InputTurn;
		}

		//LeftAxis.y = KeyW.pressed()*40 - KeyS.pressed()*40;
		//LeftAxis.x = KeyD.pressed()*40 - KeyA.pressed()*40;
		//InputTurn = KeyRight.pressed()*40 - KeyLeft.pressed()*40;

		Print << Scene::DeltaTime()*1000;

		steer.Update(LeftAxis, InputTurn, 0);

		std::array<double, 4>length = { steer.GetLF_l() ,steer.GetRF_l() ,steer.GetRB_l() ,steer.GetLB_l() };
		std::array<double, 4>angle  = { steer.GetLF_a() ,steer.GetRF_a() ,steer.GetRB_a() ,steer.GetLB_a() };
		robot.SetPower(length ,angle ).draw(color);
	}
}
