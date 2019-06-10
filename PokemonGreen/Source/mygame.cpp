/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g)
    : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(0);	// 一開始的loading進度為0%
    //
    // 開始載入資料
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

    Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
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
			GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
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
    else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
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
		log.OnMove();	// 貼上logo
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
// 這個class為遊戲的結束狀態(Game Over)
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
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
    //
    // 開始載入資料
    //
    Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 最終進度為100%
    //
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, "Game Over ! (%d)", counter / 30);
    pDC->TextOut(240, 210, str);
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
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
	gameMap->LoadBitmap();					// 載入背景的圖形
    hero.Initialize();
    hero.SetXY(97 * SM + HERO_X, 80 * SM + HERO_Y + 20);
    myMenu.Init();
	atkInterface.ReceiveBag(myMenu.GetBag());
	atkInterface.ReceivePmMenu(myMenu.GetPokemonMenu());
	atkInterface.Init();
	characters = new Characters(&atkInterface);
	characters->InitNpcs();
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
    //
    // 如果希望修改cursor的樣式，則將下面程式的commment取消即可
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

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
    //
    // 開始載入資料
   
    hero.LoadBitmap();
    testDialog.InitDialog('s');
    atkInterface.LoadBitmap();
    myMenu.LoadBitmap();

    //
    // 完成部分Loading動作，提高進度
    //
    ShowInitProgress(50);
    Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 繼續載入其他資料
    // 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
    //
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT = 0x25; // keyboard左箭頭
    const char KEY_UP = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN = 0x28; // keyboard下箭頭
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
    const char KEY_LEFT = 0x25; // keyboard左箭頭
    const char KEY_UP = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN = 0x28; // keyboard下箭頭

    if (nChar == KEY_LEFT)
        hero.SetMovingLeft(false);
    else if (nChar == KEY_RIGHT)
        hero.SetMovingRight(false);
    else if (nChar == KEY_UP)
        hero.SetMovingUp(false);
    else if (nChar == KEY_DOWN)
        hero.SetMovingDown(false);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
    hero.SetMovingLeft(false);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
    hero.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
    // 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
    hero.SetMovingRight(false);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
    hero.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
    //
    //  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
    //        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
    //        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
    //
    //
    //  貼上背景圖、撞擊數、球、擦子、彈跳的球
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