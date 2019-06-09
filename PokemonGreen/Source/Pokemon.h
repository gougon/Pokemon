#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>
#include "Skill.h"
#include "PmValue.h"
#include "Status.h"
#include "CPickableObject.h"

using namespace std;
namespace game_framework {
	constexpr auto ALL_PM_NUM = 1;
	constexpr auto V = 32;
	
	enum PmType {
		my, enemy
	};

	enum Attribute {
		normal, fighting, flying, poison,
		ground, rock, bug, ghost, steel,
		fire, water, grass, electric,
		psychic, ice, dragon, dark
	};

	class Skill;
	class Status;
	class Pokemon {
	public:
		Pokemon();
		~Pokemon();
		virtual void Init(string Name) = 0;
		void OnShow();
		void OnShow(string);
		Attribute GetAttribute();
		virtual void LoadBitmap() = 0;
		void LoadValue();
		void AddSkill(Skill *skill);
		bool AddExp(int addExp);
		string GetName();
		int GetLevel();
		int GetCatchRate();
		int GetHP();
		int GetSpeed();
		int GetAtk();
		int GetDef();
		int GetSatk();
		int GetSdef();
		int GetRemainHP();
		int GetRemainSpeed();
		int GetRemainAtk();
		int GetRemainDef();
		int GetRemainSatk();
		int GetRemainSdef();
		int GetSpeedLevel();
		int GetAtkLevel();
		int GetDefLevel();
		int GetSatkLevel();
		int GetSdefLevel();
		float GetHitRate();
		float GetEvasionRate();
		int GetNowExp();
		int GetNeedExp();
		int GetBasicExp();
		Skill *GetSkill(int order);
		int GetSkillNum();
		int GetHeight();
		Status *GetStatus();
		PmType GetPmType();
		CMovingBitmap GetIcon();
		CMovingBitmap GetFrontImage();
		bool IsCanMove();
		int Left();
		int Top();
		void SetHP(int hp);
		void SetLevel(int lv);
		void SetRemainHP(int hp);
		void SetRemainSpeed(int lv);
		void SetRemainAtk(int lv);
		void SetRemainDef(int lv);
		void SetRemainSatk(int lv);
		void SetRemainSdef(int lv);
		void SetNowExp(int exp);
		void SetNeedExp(int exp);
		void SetTopLeft(int left, int top);
		void SetHeight(int height);
		void SetStatus(int rstatu);
		void SetCanMove(bool flag);
		void SetTakeItem(int itemID);
        int GetTakeItem();
		void RoundStartStatuEffect();
		string RoundProgressStatuEffect();
		void RoundEndStatuEffect();

		int exp[30] = {														// 設定經驗值道30等
			6, 15, 30, 49, 72, 102, 135, 174, 217, 264,
			318, 374, 438, 505, 576, 654, 735, 822, 913, 1008,
			1110, 1215, 1326, 1441, 1560, 1686, 1815, 1950, 2089, 2232
		};
	protected:
		void LearnSkill();
		PmType pmtype;
		string name;
		Attribute attribute;
		Status *statu;
		int level, catchRate;
		PmValue speciesStrength, individualValue, effortValue, mixValue, remainValue;
		float hitRate, evasionRate;
		int nowExp, needExp, basicExp;
		multimap<int, Skill*> skillTree;
		set<Skill*> skills;
		CMovingBitmap frontImg, backImg, icon;
		bool haveItem = false, canMove;
        int takeItemID = -1;
	private:
		void SetValueLevel(int &rvalue, int mvalue, int level);
		int GetValueLevel(int rvalue, int mvalue);
	};
}
