/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <fstream>

namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g)
    : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
    //
    // ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
    //
    // �}�l���J���
    //
    menu.AddBitmap(HOME);
	menu.AddBitmap(HOME1);
	menu.AddBitmap(HOME2);
	menu.AddBitmap(HOME3);
	menu.AddBitmap(HOME4);
	menu.AddBitmap(HOME5);
	menu.AddBitmap(HOME6);
	menu.AddBitmap(HOME7);
	menu.AddBitmap(HOME6);
	menu.AddBitmap(HOME5);
	menu.AddBitmap(HOME4);
	menu.AddBitmap(HOME3);
	menu.AddBitmap(HOME2);
	menu.AddBitmap(HOME1);
	menu.SetDelayCount(4);
    log.AddBitmap(HOME_LOG, RGB(255, 0, 0));
    log.AddBitmap(HOME_LOG, RGB(255, 0, 0));
    log.AddBitmap(HOME_LOG_BLANK, RGB(255, 0, 0));
    log.SetDelayCount(6);
	about.AddBitmap(HOME_ABOUT, RGB(255, 0, 0));
	about.AddBitmap(HOME_ABOUT, RGB(255, 0, 0));
	about.AddBitmap(HOME_LOG_BLANK, RGB(255, 0, 0));
	about.SetDelayCount(6);
	operation.AddBitmap(HOME_CHEAT, RGB(255, 0, 0));
	operation.AddBitmap(HOME_CHEAT, RGB(255, 0, 0));
	operation.AddBitmap(HOME_LOG_BLANK, RGB(255, 0, 0));
	operation.SetDelayCount(6);
	cursor.LoadBitmap(IDB_CURSOR, RGB(255, 0, 0));
	aboutPage.LoadBitmap(IDB_ABOUT_PAGE);
	operationPage.LoadBitmap(IDB_OPERATION_PAGE);

	menu.SetTopLeft(0, 0);
	log.SetTopLeft(120, 250);
	about.SetTopLeft(120, 300);
	operation.SetTopLeft(120, 350);
	aboutPage.SetTopLeft(0, 0);
	operationPage.SetTopLeft(0, 0);
	cursor.SetTopLeft(95, 250);

	cursorPosition = 0;
	isSelected = false;

    Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
    //
    // ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
    //
	CAudio::Instance()->Load(AUDIO_MART, "Sounds//PokeMart.mp3");
    CAudio::Instance()->Load(AUDIO_HOME, "Sounds//home.wav");
    CAudio::Instance()->Load(AUDIO_WEIBAITOWN, "Sounds//weibaitown.wav");
	CAudio::Instance()->Load(AUDIO_BATTLE_START, "Sounds//battlestart.wav");
	CAudio::Instance()->Load(AUDIO_BATTLE_PROCESS, "Sounds//battleprocess.wav");
	CAudio::Instance()->Load(AUDIO_BATTLE_END, "Sounds//battleend.wav");
	CAudio::Instance()->Load(AUDIO_SELECT, "Sounds//select.wav");
	CAudio::Instance()->Load(AUDIO_START_MENU, "Sounds//startmenu.wav");
	CAudio::Instance()->Load(AUDIO_EMBER, "Sounds//ember.wav");
	CAudio::Instance()->Load(AUDIO_IMPACT, "Sounds//impact.wav");
	CAudio::Instance()->Load(AUDIO_BURN, "Sounds//burn.wav");
	CAudio::Instance()->Load(AUDIO_FREEZE, "Sounds//freeze.wav");
	CAudio::Instance()->Load(AUDIO_PARALYSIS, "Sounds//paralysis.wav");
	CAudio::Instance()->Load(AUDIO_POISON, "Sounds//poison.wav");
	CAudio::Instance()->Load(AUDIO_LOW_HP, "Sounds//lowhp.wav");
	CAudio::Instance()->Load(AUDIO_LEER, "Sounds//leer.wav");
	CAudio::Instance()->Load(AUDIO_CONFUSION, "Sounds//confusion.wav");
	CAudio::Instance()->Load(AUDIO_CLAW, "Sounds//claw.wav");
	CAudio::Instance()->Load(AUDIO_SCARYFACE, "Sounds//scaryface.wav");
	CAudio::Instance()->Load(AUDIO_LICK, "Sounds//lick.wav");
	CAudio::Instance()->Load(AUDIO_POISONGAS, "Sounds//poisongas.wav");
	CAudio::Instance()->Load(AUDIO_POWDERSNOW, "Sounds//powdersnow.wav");
	CAudio::Instance()->Load(AUDIO_SLUDGE, "Sounds//throwsludge.wav");
	CAudio::Instance()->Load(AUDIO_FLAMETHROWER, "Sounds//flamethrower.wav");
	CAudio::Instance()->Load(AUDIO_THUNDERBOLT, "Sounds//thunderbolt.wav");
	CAudio::Instance()->Load(AUDIO_BUBBLEBEAM, "Sounds//bubblebeam.wav");
	CAudio::Instance()->Load(AUDIO_WATERGUN, "Sounds//watergun.wav");
	CAudio::Instance()->Load(AUDIO_CRUNCH, "Sounds//crunch.wav");
	CAudio::Instance()->Load(AUDIO_LEAFBLADE, "Sounds//leafblade.wav");
	CAudio::Instance()->Load(AUDIO_LEAFSTORM, "Sounds//leafstorm.wav");
	CAudio::Instance()->Load(AUDIO_AURORABEAM, "Sounds//aurorabeam.wav");
	CAudio::Instance()->Load(AUDIO_CHARGE, "Sounds//charge.wav");
	CAudio::Instance()->Load(AUDIO_HYPERBEAM, "Sounds//hyperbeam.wav");
	CAudio::Instance()->Load(AUDIO_PSYCHOBOOST, "Sounds//psychoboost.wav");
	CAudio::Instance()->Load(AUDIO_NIGHTSHADE, "Sounds//nightshade.wav");
	CAudio::Instance()->Load(AUDIO_SWIFT, "Sounds//swift.wav");
	CAudio::Instance()->Load(AUDIO_LEERNE, "Sounds//leerne.wav");
	CAudio::Instance()->Load(AUDIO_ESCAPE, "Sounds//escape.wav");
	CAudio::Instance()->Load(AUDIO_GOTOBATTLE, "Sounds//gotobattle.wav");
	CAudio::Instance()->Load(AUDIO_HOSPITAL_START, "Sounds//hospitalstart.wav");
	CAudio::Instance()->Load(AUDIO_HOSPITAL_PROCESS, "Sounds//hospitalprocess.wav");
	CAudio::Instance()->Load(AUDIO_COLLISION, "Sounds//collision.wav");
	CAudio::Instance()->Load(AUDIO_PUT_HEALBALL, "Sounds//puthealball.wav");
	CAudio::Instance()->Load(AUDIO_HEAL, "Sounds//heal.wav");
	CAudio::Instance()->Play(AUDIO_HOME);
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_ESC = 27;
    const char KEY_Z = 0x5a;
	const char KEY_X = 0x58;
	const char KEY_UP = 0x26;
	const char KEY_DOWN = 0x28;

	if (nChar == KEY_Z) {
		CAudio::Instance()->Play(AUDIO_SELECT);
		isSelected = true;
		if (cursorPosition == 0)
			GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	}
	else if (nChar == KEY_X) {
		CAudio::Instance()->Play(AUDIO_SELECT);
		isSelected = false;
	}
	else if (nChar == KEY_DOWN && cursorPosition < 2) {
		CAudio::Instance()->Play(AUDIO_SELECT);
		cursorPosition++;
		cursor.SetTopLeft(95, cursor.Top() + 50);
	}
	else if (nChar == KEY_UP && cursorPosition > 0) {
		CAudio::Instance()->Play(AUDIO_SELECT);
		cursorPosition--;
		cursor.SetTopLeft(95, cursor.Top() - 50);
	}
    else if (nChar == KEY_ESC)								// Demo �����C������k
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateInit::OnShow()
{
	if (isSelected) {
		if (cursorPosition == 1)
			aboutPage.ShowBitmap();
		else if (cursorPosition == 2)
			operationPage.ShowBitmap();
	}
	else {
		menu.OnMove();
		log.OnMove();	// �K�Wlogo
		about.OnMove();
		operation.OnMove();
		menu.OnShow();
		log.OnShow();
		about.OnShow();
		operation.OnShow();
		cursor.ShowBitmap();
	}
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame* g)
    : CGameState(g)
{
}

void CGameStateOver::OnMove()
{
    counter--;

    if (counter < 0)
        GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
    counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
    //
    // ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
    //
    // �}�l���J���
    //
    Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
    //
    // �̲׶i�׬�100%
    //
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
    CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
    fp = pDC->SelectObject(&f);					// ��� font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
    sprintf(str, "Game Over ! (%d)", counter / 30);
    pDC->TextOut(240, 210, str);
    pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
    CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g)
    : CGameState(g)
{
	gameMap = nullptr;
}

CGameStateRun::~CGameStateRun()
{
	delete gameMap;
	delete characters;
}

void CGameStateRun::OnBeginState()
{
    CAudio::Instance()->Stop(AUDIO_HOME);
	gameMap = new WeiBaiMap(&gameEvent);
	gameMap->LoadBitmap();					// ���J�I�����ϧ�
    hero.Initialize();
    hero.SetXY(97 * SM + HERO_X, 80 * SM + HERO_Y + 20);
    myMenu.Init();
	atkInterface.ReceiveBag(myMenu.GetBag());
	atkInterface.ReceivePmMenu(myMenu.GetPokemonMenu());
	atkInterface.Init();
	characters = new Characters(&atkInterface);
	characters->InitNpcs();
}

void CGameStateRun::OnMove()							// ���ʹC������
{
    //
    // �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
    //
    // SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
    //
    if (atkInterface.IsWork())
    {
        atkInterface.OnMove();
    }
    else if (myMenu.IsWork())
    {
        myMenu.OnMove();
    }
    else
    {
        testDialog.OnMove();
		gameMap->OnMove();
        int count = hero.GetCount();
        if (hero.IsCanMove())
        {
			int oneBlockTime = SM / hero.GetSpeed();
            if (!hero.IsMoving() && count >= oneBlockTime && !hero.IsJumping())
            {
                hero.SetCanMove(false);
                hero.SetCount(0);
            }
            else if (count >= oneBlockTime && !hero.IsJumping())
            {
                hero.SetCount(0);
            }
            else
            {
                hero.SetCount(++count);
                hero.OnMove(&gameMap, atkInterface, characters);
            }
        }
		characters->OnMove(hero, *gameMap);
    }
	if (hero.GetGameEvent(winMaster)) {
		GotoGameState(GAME_STATE_OVER);
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
    //
    // ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
    //
    // �}�l���J���
   
    hero.LoadBitmap();
    testDialog.InitDialog('s');
    atkInterface.LoadBitmap();
    myMenu.LoadBitmap();

    //
    // ��������Loading�ʧ@�A�����i��
    //
    ShowInitProgress(50);
    Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
    //
    // �~����J��L���
    // ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
    //
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT = 0x25; // keyboard���b�Y
    const char KEY_UP = 0x26; // keyboard�W�b�Y
    const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
    const char KEY_DOWN = 0x28; // keyboard�U�b�Y
    const char KEY_ENTER = 0x0d;
    const char KEY_Z = 0x5a;

    if (atkInterface.IsWork())
    {
        atkInterface.KeyDownListener(nChar);
    }
    else if (nChar == KEY_ENTER)
    {
        myMenu.Start();
		myMenu.SetMoney(hero.GetMoney());
        myMenu.SetPokemons(hero.GetPokemons());
    }
    else if (myMenu.IsWork())
    {
        myMenu.KeyDownListener(nChar);
    }
	else if (characters->IsTalk()) {
		characters->KeyDownListener(nChar, hero, *gameMap);
	}
    else
    {
        hero.SetCanMove(true);

        if (!hero.IsMoving() && hero.GetCount() == 0)
        {
            hero.ReceiveData(gameMap, &myMenu);
            hero.KeyIn(nChar, characters, *gameMap);
        }
		gameMap->KeyDownListener(nChar, hero);
    }
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT = 0x25; // keyboard���b�Y
    const char KEY_UP = 0x26; // keyboard�W�b�Y
    const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
    const char KEY_DOWN = 0x28; // keyboard�U�b�Y

    if (nChar == KEY_LEFT)
        hero.SetMovingLeft(false);
    else if (nChar == KEY_RIGHT)
        hero.SetMovingRight(false);
    else if (nChar == KEY_UP)
        hero.SetMovingUp(false);
    else if (nChar == KEY_DOWN)
        hero.SetMovingDown(false);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
    hero.SetMovingLeft(false);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
    hero.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
    // �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
    hero.SetMovingRight(false);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
    hero.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
    //
    //  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
    //        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
    //        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
    //
    //
    //  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
    if (atkInterface.IsWork())
        atkInterface.OnShow();
    else {
        gameMap->OnShow();
		characters->OnShow(hero, *gameMap);
        hero.OnShow();
		gameMap->ReShow(hero);
		characters->ReShow(hero, *gameMap);
        if (myMenu.IsWork())
            myMenu.OnShow();
    }
}
}