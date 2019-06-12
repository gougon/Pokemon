#pragma once
#include "CText.h"
namespace game_framework
{
	class CSelf
	{
	public:
		CSelf();
		void LoadBitmap();
		void OnShow();
	private:
		CMovingBitmap self_image;
	};
}