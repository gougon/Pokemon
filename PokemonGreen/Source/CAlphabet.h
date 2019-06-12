#pragma once
namespace game_framework
{
	class CAlphabet {
	public:
		void LoadBitmap();
		CMovingBitmap* GetAlphabet(char alphaID);
	private:
		CMovingBitmap alphabet_list[41];
	};
}