#pragma once
#include <string>
#include <vector>
#include "ActionObject.h"

using namespace std;
namespace game_framework {
	class Illustration : public ActionObject {
	public:
		void Init();
		void OnShow();
		void OnMove();
		void LoadBitmap();
		void KeyDownListener(UINT nChar);
		virtual void SetTopLeft() {}
	private:
	};
}
