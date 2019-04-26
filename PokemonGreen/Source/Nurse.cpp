#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Nurse.h"

namespace game_framework {
	Nurse::Nurse()
	{
		Init();
	}

	void Nurse::Init()
	{
		count = 0;
		dialogBox.InitDialog('n');
	}

	void Nurse::OnShow()
	{

	}

	void Nurse::OnMove()
	{
		switch (count) {
		case 0:
			dialogBox.SetText("good effort!;" + 
				"");
		}
	}

	void Nurse::LoadBitmap()
	{

	}

	void Nurse::KeyDownListener(UINT nChar)
	{
		const char KEY_UP = 0x26;
		const char KEY_DOWN = 0x28;
		const char KEY_LEFT = 0x25;
		const char KEY_RIGHT = 0x27;
		const char KEY_Z = 0x5a;
		const char KEY_X = 0x58;

		switch (nChar) {
		case KEY_Z:
			++count;
			break;
		}
	}

	void Nurse::ReceiveData(vector<Pokemon*>* pokemons)
	{
		this->pokemons = pokemons;
	}
}