#pragma once

#include <string>
#include "Pokemon.h"
#include "CText.h"

using namespace std;
namespace game_framework {
	constexpr auto MYX = 340;
	constexpr auto ENEX = 30;
	constexpr auto MYY = 220;
	constexpr auto ENEY = 40;
	constexpr auto HP_MYX = 462;
	constexpr auto HP_MYY = 268;
	constexpr auto HP_ENEX = 132;
	constexpr auto HP_ENEY = 85;
	constexpr auto HP_LEN = 135.0;
	constexpr auto EXP_X = 424;
	constexpr auto EXP_Y = 318;
	constexpr auto EXP_LEN = 173.0;
	constexpr auto MY_STATU_ICON_X = 100;
	constexpr auto MY_STATU_ICON_Y = 100;
	constexpr auto ENE_STATU_ICON_X = 100;
	constexpr auto ENE_STATU_ICON_Y = 100;

	enum barType {
		barTypeMy, barTypeEnemy
	};

	class AtkBar {
	public:
		AtkBar(barType rtype = barTypeMy);
		~AtkBar();
		void LoadBitmap();
		void Init();
		void OnMove();
		void OnShow();
		void SetTopLeft();
		void ReceiveType(barType rtype);	// 取得bar的type
		void ReceiveStatu(int statu);		// 取得statu
		void ReceiveData(Pokemon *rpm);		// 取得pokemon
		bool IsAddExp();	// 是否正在增加經驗值
		bool IsAnime();		// 是否正在播放動畫
	private:
		const int V = 5;
		const int MY_FIRST_ROW = 225;
		const int ENE_FIRST_ROW = 45;
		const int MY_SECOND_ROW = 275;
		const int MY_NAME_RIGHT = 505;
		const int ENE_NAME_RIGHT = 175;
		const int MY_LV_LEFT = 550;
		const int ENE_LV_LEFT = 220;
		const int MY_RHP_RIGHT = 505;
		const int MY_HP_LEFT = 530;
		void InitBarByType();
		void InitHp();
		void SetHpBarWidth(int width);		// 設定hp的寬度
		int x;		 // 從右邊算
		double hpWidthRate;
		bool isAddExp, isSetLowHpAudio;
		Pokemon *pm;
		barType type;
		CText nameText, lvText, remainHpText, allHpText;
		CMovingBitmap myBar, enemyBar, greenHP, yellowHP, redHP, *targetHpBar, expBar;
		CMovingBitmap burnIcon, poisonIcon, freezeIcon, paralysisIcon, *statuIcon;
	};
}