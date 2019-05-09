#pragma once
#include <string>
#include <vector>
#include "Pokemon.h"

using namespace std;
namespace game_framework
{
	enum StatuName {
		none, statuBurn, statuFreeze, statuParalysis, statuPoison, statuSleep
	};

	class Status {
	public:
		Status();
		void SetTopLeft(int left, int top);
		void OnShow();
		void OnMove();
		void SetStatu(int rstatu);
		void RoundStartStatuEffect(Pokemon &pm);
		string RoundProgressStatuEffect(Pokemon &pm);
		void RoundEndStatuEffect(Pokemon &pm);
		int GetStatu();
		bool IsAnime();
	private:
		void BurnEffect(Pokemon &pm);
		void FreezeEffect(Pokemon &pm);
		void PoisonEffect(Pokemon &pm);
		void SleepEffect(Pokemon &pm);
		void ParalysisEffect(Pokemon &pm);
		bool IsRelieveStatu(int start, int end);
		void RelieveStatu(Pokemon &pm);

		int statu;
		int counter;
		CAnimation burnAnime;	// À³§ï¬°vector
	};
}