#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <stdlib.h>
#include "PmOprtPanel.h"

namespace game_framework {
	PmOprtPanel::PmOprtPanel() :
		ActionObject(), isItem(false), order(0)
	{
		// empty body
	}

	PmOprtPanel::~PmOprtPanel()
	{
		delete pm;
	}

	void PmOprtPanel::Init()
	{
		order = 0;
		operationPanel.SetTopLeft(PANEL_LEFT, PANEL_TOP);
		cursor.SetTopLeft(CURSOR_LEFT, CURSOR_TOP);

		pmOprtView.Init();
	}

	void PmOprtPanel::OnShow()
	{
		if (!isItem) {
			operationPanel.ShowBitmap();
			cursor.ShowBitmap();
		}
		else {
			if (order == pmOprtPanelSltView) {
				pmOprtView.OnShow();
			}
		}
	}

	void PmOprtPanel::OnMove()
	{
		if (!isItem) {
			cursor.SetTopLeft(CURSOR_LEFT, CURSOR_TOP + CURSOR_INTERVAL * order);
		}
		else {
			switch (order) {
			case pmOprtPanelSltView:
				pmOprtView.OnMove();
				if (!pmOprtView.IsWork()) {
					isItem = false;
				}
				break;
			case pmOprtPanelSltChange:
				break;
			case pmOprtPanelSltItem:
				break;
			case pmOprtPanelSltClose:
				End();
				break;
			}
		}
	}

	void PmOprtPanel::LoadBitmap()
	{
		operationPanel.LoadBitmap(IDB_POKEMON_OPERATION_PANEL);
		cursor.LoadBitmap(IDB_ATK_CURSOR);

		pmOprtView.LoadBitmap();
	}

	void PmOprtPanel::KeyDownListener(UINT nChar)
	{
		const char KEY_UP = 0x26;
		const char KEY_DOWN = 0x28;
		const char KEY_Z = 0x5a;
		const char KEY_X = 0x58;

		if (!isItem) {
			switch (nChar) {
			case KEY_UP:
				if (order > 0) {
					order -= 1;
				}
				break;
			case KEY_DOWN:
				if (order < 4) {
					order += 1;
				}
				break;
			case KEY_Z:
				isItem = true;
				if (order == pmOprtPanelSltView) {
					pmOprtView.Start();
				}
				break;
			case KEY_X:
				End();
				break;
			default:
				break;
			}
		}
		else {
			switch (order) {
			case pmOprtPanelSltView:
				pmOprtView.KeyDownListener(nChar);
				break;
			case pmOprtPanelSltChange:
				break;
			case pmOprtPanelSltItem:
				break;
			case pmOprtPanelSltClose:
				break;
			default:
				break;
			}
		}
	}

	void PmOprtPanel::End()
	{
		order = 0;
		isWork = false;
		isItem = false;
	}

}