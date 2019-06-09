#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Status.h"

namespace game_framework {
	Status::Status() :
		statu(none), counter(0)
	{
		burnAnime.AddBitmap(IDB_SKILL_EMBER10, RGB(255, 0, 0));
		burnAnime.AddBitmap(IDB_SKILL_EMBER11, RGB(255, 0, 0));
		burnAnime.AddBitmap(IDB_SKILL_EMBER12, RGB(255, 0, 0));
		burnAnime.AddBitmap(IDB_SKILL_EMBER13, RGB(255, 0, 0));
		burnAnime.AddBitmap(IDB_SKILL_EMBER14, RGB(255, 0, 0));
		burnAnime.AddBitmap(IDB_SKILL_EMBER15, RGB(255, 0, 0));
		burnAnime.AddBitmap(IDB_SKILL_EMBER16, RGB(255, 0, 0));
		burnAnime.AddBitmap(IDB_SKILL_EMBER17, RGB(255, 0, 0));
		burnAnime.AddBitmap(IDB_SKILL_EMBER18, RGB(255, 0, 0));
		burnAnime.SetDelayCount(1);
		poisonAnime.AddBitmap(IDB_SKILL_SLUDGE11, RGB(255, 0, 0));
		poisonAnime.AddBitmap(IDB_SKILL_SLUDGE12, RGB(255, 0, 0));
		poisonAnime.AddBitmap(IDB_SKILL_SLUDGE13, RGB(255, 0, 0));
		poisonAnime.AddBitmap(IDB_SKILL_SLUDGE14, RGB(255, 0, 0));
		poisonAnime.AddBitmap(IDB_SKILL_SLUDGE15, RGB(255, 0, 0));
		poisonAnime.SetDelayCount(2);
		freezeAnime.AddBitmap(IDB_SKILL_POWDERSNOW16, RGB(255, 0, 0));
		freezeAnime.AddBitmap(IDB_SKILL_POWDERSNOW17, RGB(255, 0, 0));
		freezeAnime.AddBitmap(IDB_SKILL_POWDERSNOW18, RGB(255, 0, 0));
		freezeAnime.AddBitmap(IDB_SKILL_POWDERSNOW19, RGB(255, 0, 0));
		freezeAnime.AddBitmap(IDB_SKILL_POWDERSNOW20, RGB(255, 0, 0));
		freezeAnime.AddBitmap(IDB_SKILL_POWDERSNOW21, RGB(255, 0, 0));
		freezeAnime.SetDelayCount(2);
		paralysisAnime.AddBitmap(IDB_SKILL_THUNDERBOLT5, RGB(255, 0, 0));
		paralysisAnime.AddBitmap(IDB_SKILL_THUNDERBOLT6, RGB(255, 0, 0));
		paralysisAnime.AddBitmap(IDB_SKILL_THUNDERBOLT7, RGB(255, 0, 0));
		paralysisAnime.AddBitmap(IDB_SKILL_THUNDERBOLT8, RGB(255, 0, 0));
		paralysisAnime.AddBitmap(IDB_SKILL_THUNDERBOLT9, RGB(255, 0, 0));
		paralysisAnime.SetDelayCount(2);
	}
	
	void Status::SetTopLeft(int left, int top)
	{
		burnAnime.SetTopLeft(left, top);
		poisonAnime.SetTopLeft(left, top);
		freezeAnime.SetTopLeft(left, top);
		paralysisAnime.SetTopLeft(left, top);
	}

	void Status::SetStatu(int rstatu)
	{
		statu = rstatu;
		counter = (statu == none) ? 0 : counter;
	}

	void Status::OnShow()
	{
		switch (statu) {
		case statuBurn:
			burnAnime.OnShow();
			break;
		case statuFreeze:
			freezeAnime.OnShow();
			break;
		case statuParalysis:
			paralysisAnime.OnShow();
			break;
		case statuPoison:
			poisonAnime.OnShow();
			break;
		default:
			break;
		}
	}

	void Status::OnMove()
	{
		burnAnime.OnMove();
		poisonAnime.OnMove();
		freezeAnime.OnMove();
		paralysisAnime.OnMove();
	}

	void Status::RoundStartStatuEffect(Pokemon &pm)
	{
		if (statu == none)
			return;
		switch (statu) {
		case statuFreeze:
			FreezeEffect(pm);
			if (IsRelieveStatu(5, 5))
				RelieveStatu(pm);
			break;
		case statuSleep:
			SleepEffect(pm);
			if (IsRelieveStatu(2, 5))
				RelieveStatu(pm);
			break;
		case statuParalysis:
			ParalysisEffect(pm);
			break;
		}
		++counter;
	}

	string Status::RoundProgressStatuEffect(Pokemon &pm)
	{
		if (statu == none)
			return "none";
		switch (statu) {
		case statuFreeze:
			CAudio::Instance()->Play(AUDIO_FREEZE);
			return pm.GetName() + " is freezing";
			break;
		case statuSleep:
			return pm.GetName() + " is sleeping";
			break;
		case statuParalysis:
			CAudio::Instance()->Play(AUDIO_PARALYSIS);
			return pm.GetName() + " is paralysising";
			break;
		default:
			return "none";
		}
	}

	void Status::RoundEndStatuEffect(Pokemon &pm)
	{
		if (statu == none)
			return;
		switch (statu) {
		case statuBurn:
			CAudio::Instance()->Play(AUDIO_BURN);
			BurnEffect(pm);
			break;
		case statuPoison:
			CAudio::Instance()->Play(AUDIO_POISON);
			PoisonEffect(pm);
			break;
		}
	}

	int Status::GetStatu()
	{
		return statu;
	}

	bool Status::IsAnime()
	{
		if (burnAnime.IsFinalBitmap()) {
			burnAnime.Reset();
			return false;
		}
		if (poisonAnime.IsFinalBitmap()) {
			poisonAnime.Reset();
			return false;
		}
		if (freezeAnime.IsFinalBitmap()) {
			freezeAnime.Reset();
			return false;
		}
		if (poisonAnime.IsFinalBitmap()) {
			poisonAnime.Reset();
			return false;
		}
		return true;
	}

	// private

	void Status::BurnEffect(Pokemon &pm)
	{
		pm.SetRemainHP(pm.GetRemainHP() - (pm.GetHP() / 16));
	}

	void Status::FreezeEffect(Pokemon &pm)
	{
		pm.SetCanMove(false);
	}

	void Status::PoisonEffect(Pokemon &pm)
	{
		pm.SetRemainHP(pm.GetRemainHP() - (pm.GetHP() / 16));
	}

	void Status::SleepEffect(Pokemon &pm)
	{
		pm.SetCanMove(false);
	}

	void Status::ParalysisEffect(Pokemon &pm)
	{
		pm.SetCanMove(false);
	}

	bool Status::IsRelieveStatu(int start, int end)
	{
		if (counter >= start && counter <= end) {
			int rnd = rand() % 2;
			if (rnd == 0)
				return true;
		}
		else if (counter > end)
			return true;
		return false;
	}

	void Status::RelieveStatu(Pokemon &pm)
	{
		counter = 0;
		statu = none;
		pm.SetCanMove(true);
	}
}