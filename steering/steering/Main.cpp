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
		if (const auto gamepad=Gamepad(1)) {
			/*ps5だったらGamepad(0)だよ*/
			//const auto& info = gamepad.getInfo();
			LeftAxis.x = (int)(gamepad.axes.at(0)*255);
			LeftAxis.y = -(int)(gamepad.axes.at(1)*255);
			InputTurn = (int)(gamepad.axes.at(3)*255);
			/*ps5だったらat(2)だよ*/
			Print << LeftAxis <<U" "<< InputTurn;
		}
		Print << Scene::DeltaTime()*1000;

		steer.Update(LeftAxis, InputTurn, 0);
		//robot.SetRF(steer.GetRF_l(), steer.GetRF_a())
		//	 .SetRB(steer.GetRB_l(), steer.GetRB_a())
		//	 .SetLF(steer.GetLF_l(), steer.GetLF_a())
		//	 .SetLB(steer.GetLB_l(), steer.GetLB_a())
		//	 .draw(color);
		std::array<double, 4>length = { steer.GetLF_l() ,steer.GetRF_l() ,steer.GetRB_l() ,steer.GetLB_l() };
		std::array<double, 4>angle  = { steer.GetLF_a() ,steer.GetRF_a() ,steer.GetRB_a() ,steer.GetLB_a() };
		robot.SetPower(length ,angle ).draw(color);
	}
}
