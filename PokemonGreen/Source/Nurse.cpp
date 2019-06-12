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
	Nurse::Nurse() :
		hero(nullptr), pokemons(nullptr), ball(nullptr)
	{
		// empty body
	}

	Nurse::~Nurse()
	{
		if (ball != nullptr) {
			delete[] ball;
			ball = nullptr;
		}
	}

	void Nurse::Init()
	{
		isAnime = false;
		count = audioCount = 0;
		choice = yes;
		dialogBox.InitDialog('n');
		ynPanel.SetTopLeft(YNPANEL_LEFT, YNPANEL_TOP);
		cursor.SetTopLeft(CURSOR_LEFT, CURSOR_TOP);
	}

	void Nurse::OnShow()
	{
		dialogBox.OnShow();
		switch (count) {
		case 1:
			ynPanel.ShowBitmap();
			cursor.ShowBitmap();
			break;
		case 2:
			if (isAnime) {
				for (int i = 0; i < pmNum; ++i) {
					if(audioCount / 10 >= i)
						ball[i].OnShow();
				}
			}
			break;
		}
	}

	void Nurse::OnMove()
	{
		switch (count) {
		case 0:
			dialogBox.SetText("good effort. this is pm hospital;it can get your pm strength back");
			break;
		case 1:
			dialogBox.SetText("do you want to take your pokemons;rest?");
			switch (choice) {
			case yes:
				cursor.SetTopLeft(CURSOR_LEFT, CURSOR_TOP);
				break;
			case no:
				cursor.SetTopLeft(CURSOR_LEFT, CURSOR_TOP2);
				break;
			}
			break;
		case 2:
			switch (choice) {
			case yes:
				audioCount++;
				isAnime = IsHealing();
				Heal();
				if (isAnime) {
					dialogBox.SetText("then... heal");

					// set put and heal audio
					if (audioCount % 10 == 1 && (audioCount+1) / 10 < pmNum)
						CAudio::Instance()->Play(AUDIO_PUT_HEALBALL);
					else if(audioCount == (pmNum-1) * 10)
						CAudio::Instance()->Play(AUDIO_HEAL);

					// heal anime start
					if (audioCount >= (pmNum - 1) * 10) {
						CAudio::Instance()->Stop(AUDIO_HOSPITAL_PROCESS);
						for (int i = 0; i < pmNum; ++i)
							ball[i].OnMove();
					}
				}
				else {
					if (audioCount == (pmNum - 1) * 10 + 60)
						CAudio::Instance()->Play(AUDIO_HOSPITAL_PROCESS);
					dialogBox.SetText("pokemons are all have strength!");
				}
				break;
			case no:
				count = 3;
				break;
			}
			break;
		case 3:
			dialogBox.SetText("welcome again!");
			break;
		}
	}

	void Nurse::LoadBitmap()
	{
		ynPanel.LoadBitmap(BG_YESNO);
		cursor.LoadBitmap(IDB_CURSOR);
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
		case KEY_UP:
			if (count == 1) {
				CAudio::Instance()->Play(AUDIO_SELECT);
				choice = yes;
			}
			break;
		case KEY_DOWN:
			if (count == 1) {
				CAudio::Instance()->Play(AUDIO_SELECT);
				choice = no;
			}
			break;
		case KEY_Z:
			if (!isAnime) {
				CAudio::Instance()->Play(AUDIO_SELECT);
				++count;
			}
			switch (count) {
			case 2:
				if (choice == yes) 
					isAnime = true;
				break;
			case 4:
				End();			// end­noverride
				break;
			}
			break;
		}
	}

	void Nurse::ReceiveData(CHero &hero)
	{
		this->hero = &hero;
		this->pokemons = hero.GetPokemons();
		pmNum = pokemons->size();
		ball = new CAnimation[pmNum];
		for (int i = 0; i < pmNum; ++i) {
			int row = i / 2;
			int col = i % 2;
			SetBall(&ball[i], row, col);
		}
	}

	void Nurse::End()
	{
		isWork = false;
		hero->EndDialog();
		isAnime = false;
		count = audioCount = choice = pmNum = 0;
		if (ball != nullptr) {
			delete[] ball;
			ball = nullptr;
		}
	}

	void Nurse::Start()
	{
		isWork = true;
		hero->StartDialog();
	}

	// private

	bool Nurse::IsHealing()
	{
		for (int i = 0; i < pmNum; ++i) {
			if (ball[i].IsFinalBitmap()) {
				return false;
			}
		}
		return true;
	}

	void Nurse::SetBall(CAnimation *ball, int row, int col)
	{
		TRACE("\nball address = %d\n", &ball);
		ball->AddBitmap(HEAL_BALL1);
		ball->AddBitmap(HEAL_BALL2);
		ball->AddBitmap(HEAL_BALL3);
		ball->AddBitmap(HEAL_BALL4);
		ball->AddBitmap(HEAL_BALL5);
		ball->AddBitmap(HEAL_BALL6);
		ball->AddBitmap(HEAL_BALL7);
		ball->AddBitmap(HEAL_BALL8);
		ball->AddBitmap(HEAL_BALL9);
		ball->AddBitmap(HEAL_BALL10);
		ball->AddBitmap(HEAL_BALL11);
		ball->AddBitmap(HEAL_BALL12);

		int left = (col == 0) ? 225 : 225 + ball->Width();
		int top = 90 + HEAL_BALL_INTERVAL * row;
		ball->SetTopLeft(left, top);
		ball->SetDelayCount(3);
	}

	void Nurse::Heal()
	{
		for (auto i : *pokemons) {
			i->SetRemainHP(i->GetHP());
			i->SetStatus(none);
		}
	}
}