#pragma once
#include <string>
#include <vector>

using namespace std;
namespace game_framework {
	class Black {
	public:
		Black();
		void Draw();
	private:
		CMovingBitmap black;
	};
}