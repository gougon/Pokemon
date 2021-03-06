#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "Functions.cpp"
#include "Pokemon.h"

namespace game_framework {
	Pokemon::Pokemon() :
		statu(nullptr), canMove(true)
	{
		statu = new Status();
		catchRate = 60;
	}

	Pokemon::~Pokemon()
	{
		delete statu;
		for (auto i : skillTree)
			delete i.second;
		for (auto i : skills)
			i = nullptr;
	}

	void Pokemon::OnShow()
	{
		if (pmtype == my) {
			backImg.ShowBitmap();
		}
		else {
			frontImg.ShowBitmap();
		}
	}

	void Pokemon::OnShow(string msg)
	{
		if (pmtype == my) {
			backImg.ShowBitmap("atk");
		}
		else {
			frontImg.ShowBitmap("atk");
		}
	}

	// Getter

	Attribute Pokemon::GetAttribute()
	{
		return attribute;
	}

	void Pokemon::LoadValue()
	{
		mixValue.hp = (level * (speciesStrength.hp + individualValue.hp) / 50) +
			((level * effortValue.hp / 100)) + 10 + level;
		mixValue.speed = (level * (speciesStrength.speed + individualValue.speed) / 50) +
			((level * effortValue.speed / 100)) + 5;
		mixValue.atk = (level * (speciesStrength.atk + individualValue.atk) / 50) +
			((level * effortValue.atk / 100)) + 5;
		mixValue.def = (level * (speciesStrength.def + individualValue.def) / 50) +
			((level * effortValue.def / 100)) + 5;
		mixValue.satk = (level * (speciesStrength.satk + individualValue.satk) / 50) +
			((level * effortValue.satk / 100)) + 5;
		mixValue.sdef = (level * (speciesStrength.sdef + individualValue.sdef) / 50) +
			((level * effortValue.sdef / 100)) + 5;
		remainValue = mixValue;
	}

	void Pokemon::AddSkill(Skill *skill)
	{
		if(skills.size() < 4)
			skills.insert(skill);
	}

	bool Pokemon::AddExp(int addExp)
	{
		int tempHp = remainValue.hp;
		nowExp += addExp;
		if (nowExp > needExp) {
			nowExp -= needExp;
			level += 1;
			LearnSkill();
			needExp = exp[level];
			LoadValue();
			remainValue.hp = ((int)(1.1 * tempHp) > mixValue.hp) ?
				mixValue.hp : (int)(1.1 * tempHp);
			return true;
		}
		return false;
	}

	string Pokemon::GetName()
	{
		return name;
	}

	pokemonName Pokemon::GetPmID()
	{
		return pmID;
	}

	int Pokemon::GetLevel()
	{
		return level;
	}

	int Pokemon::GetCatchRate()
	{
		return catchRate;
	}

	int Pokemon::GetHP()
	{
		return mixValue.hp;
	}

	int Pokemon::GetSpeed()
	{
		return mixValue.speed;
	}

	int Pokemon::GetAtk()
	{
		return mixValue.atk;
	}

	int Pokemon::GetDef()
	{
		return mixValue.def;
	}

	int Pokemon::GetSatk()
	{
		return mixValue.atk;
	}

	int Pokemon::GetSdef()
	{
		return mixValue.sdef;
	}

	int Pokemon::GetRemainHP()
	{
		return remainValue.hp;
	}

	int Pokemon::GetRemainSpeed()
	{
		return remainValue.speed;
	}

	int Pokemon::GetRemainAtk()
	{
		return remainValue.atk;
	}

	int Pokemon::GetRemainDef()
	{
		return remainValue.def;
	}

	int Pokemon::GetRemainSatk()
	{
		return remainValue.satk;
	}

	int Pokemon::GetRemainSdef()
	{
		return remainValue.sdef;
	}

	int Pokemon::GetSpeedLevel()
	{
		return GetValueLevel(remainValue.speed, mixValue.speed);
	}

	int Pokemon::GetAtkLevel()
	{
		return GetValueLevel(remainValue.atk, mixValue.atk);
	}

	int Pokemon::GetDefLevel()
	{
		return GetValueLevel(remainValue.def, mixValue.def);
	}

	int Pokemon::GetSatkLevel()
	{
		return GetValueLevel(remainValue.satk, mixValue.satk);
	}

	int Pokemon::GetSdefLevel()
	{
		return GetValueLevel(remainValue.sdef, mixValue.sdef);
	}

	float Pokemon::GetHitRate()
	{
		return hitRate;
	}

	float Pokemon::GetEvasionRate()
	{
		return evasionRate;
	}

	int Pokemon::GetNowExp()
	{
		return nowExp;
	}

	int Pokemon::GetNeedExp()
	{
		return needExp;
	}

	int Pokemon::GetBasicExp()
	{
		return basicExp;
	}

	Skill *Pokemon::GetSkill(int order)
	{
		if (order < (int)skills.size())
			return FindSetFromOrder(skills, order);
		else {
			ASSERT(0);
			return nullptr;
		}
	}

	int Pokemon::GetSkillNum()
	{
		return skills.size();
	}

	int Pokemon::GetHeight()
	{
		return (pmtype == my) ? backImg.RectHeight() : frontImg.RectHeight();
	}

	Status *Pokemon::GetStatus()
	{
		return statu;
	}

	PmType Pokemon::GetPmType()
	{
		return pmtype;
	}

	CMovingBitmap Pokemon::GetIcon()
	{
		return icon;
	}

	CMovingBitmap Pokemon::GetFrontImage()
	{
		return frontImg;
	}

	bool Pokemon::IsCanMove()
	{
		return canMove;
	}

	int Pokemon::Left()
	{
		return (pmtype == my) ? backImg.Left() : frontImg.Left();
	}

	int Pokemon::Top()
	{
		return (pmtype == my) ? backImg.Top() : frontImg.Top();
	}

	// Setter

	void Pokemon::SetHP(int hp)
	{
		mixValue.hp = hp;
		LoadValue();
	}

	void Pokemon::SetLevel(int lv)
	{
		level = lv;
		needExp = exp[level];
		LearnSkill();
		LoadValue();
	}

	void Pokemon::SetRemainHP(int hp)
	{
		remainValue.hp = hp;
	}

	void Pokemon::SetRemainSpeed(int lv)
	{
		SetValueLevel(remainValue.speed, mixValue.speed, lv);
	}

	void Pokemon::SetRemainAtk(int lv)
	{
		SetValueLevel(remainValue.atk, mixValue.atk, lv);
	}

	void Pokemon::SetRemainDef(int lv)
	{
		SetValueLevel(remainValue.def, mixValue.def, lv);
	}

	void Pokemon::SetRemainSatk(int lv)
	{
		SetValueLevel(remainValue.satk, mixValue.satk, lv);
	}

	void Pokemon::SetRemainSdef(int lv)
	{
		SetValueLevel(remainValue.sdef, mixValue.sdef, lv);
	}

	void Pokemon::SetNowExp(int exp)
	{
		nowExp = exp;
	}

	void Pokemon::SetNeedExp(int exp)
	{
		needExp = exp;
	}

	void Pokemon::SetTopLeft(int left, int top)
	{
		if (pmtype == my) {
			backImg.SetTopLeft(left, top);
		}
		else {
			frontImg.SetTopLeft(left, top);
		}

	}

	void Pokemon::SetHeight(int height)
	{
		if (pmtype == my) {
			backImg.SetHeight(height);
		}
		else {
			frontImg.SetHeight(height);
		}
	}

	void Pokemon::SetStatus(int rstatu)
	{
		statu->SetStatu(rstatu);
	}

	void Pokemon::SetCanMove(bool flag)
	{
		canMove = flag;
	}
	void Pokemon::SetTakeItem(int itemID)
	{
		takeItemID = itemID;
	}

    int Pokemon::GetTakeItem()
    {
        if (takeItemID == -1) return -1;
        else return takeItemID;
    }

	void Pokemon::RoundStartStatuEffect()
	{
		statu->RoundStartStatuEffect(*this);
	}

	string Pokemon::RoundProgressStatuEffect()
	{
		return statu->RoundProgressStatuEffect(*this);
	}

	void Pokemon::RoundEndStatuEffect()
	{
		statu->RoundEndStatuEffect(*this);
	}

	// protected

	void Pokemon::LearnSkill()
	{
		for (auto i : skillTree) {
			if (i.first <= level)
				skills.insert(i.second);
		}
	}

	// private

	void Pokemon::SetValueLevel(int &rvalue, int mvalue, int level)
	{
		switch (level) {
		case -6:
			rvalue = (int)(mvalue * 0.33);
			break;
		case -5:
			rvalue = (int)(mvalue * 0.38);
			break;
		case -4:
			rvalue = (int)(mvalue * 0.43);
			break;
		case -3:
			rvalue = (int)(mvalue * 0.50);
			break;
		case -2:
			rvalue = (int)(mvalue * 0.60);
			break;
		case -1:
			rvalue = (int)(mvalue * 0.75);
			break;
		case 0:
			rvalue = (int)(mvalue * 1.00);
			break;
		case 1:
			rvalue = (int)(mvalue * 1.33);
			break;
		case 2:
			rvalue = (int)(mvalue * 1.67);
			break;
		case 3:
			rvalue = (int)(mvalue * 2.00);
			break;
		case 4:
			rvalue = (int)(mvalue * 2.33);
			break;
		case 5:
			rvalue = (int)(mvalue * 2.67);
			break;
		case 6:
			rvalue = (int)(mvalue * 3.00);
			break;
		}
	}

	int Pokemon::GetValueLevel(int rvalue, int mvalue)
	{
		float rate = rvalue / (float)mvalue;
		if (rate <= 0.33) return -6;
		else if (rate <= 0.38) return -5;
		else if (rate <= 0.43) return -4;
		else if (rate <= 0.50) return -3;
		else if (rate <= 0.60) return -2;
		else if (rate <= 0.75) return -1;
		else if (rate <= 1.00) return 0;
		else if (rate <= 1.33) return 1;
		else if (rate <= 1.67) return 2;
		else if (rate <= 2.00) return 3;
		else if (rate <= 2.33) return 4;
		else if (rate <= 2.67) return 5;
		else return 6;
	}
}
