#pragma once
#include <string>
#include <vector>

using namespace std;
namespace game_framework {
	class Black {
	public:
		Black();
		static Black* Instance();
		void Draw();
	private:
		static Black delay;
		CMovingBitmap black;
	};
}