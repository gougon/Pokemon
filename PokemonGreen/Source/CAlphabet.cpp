#include "stdafx.h"
#include "Resource.h"
#include <string>
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CAlphabet.h"
namespace game_framework
{
CAlphabet::CAlphabet()
{
}

CAlphabet::~CAlphabet()
{
}

void CAlphabet::LoadBitmap()
{
    alphabet_list[0].LoadBitmap(IDB_ALPHABET_SMALL_A, RGB(255, 0, 0));
    alphabet_list[1].LoadBitmap(IDB_ALPHABET_SMALL_B, RGB(255, 0, 0));
    alphabet_list[2].LoadBitmap(IDB_ALPHABET_SMALL_C, RGB(255, 0, 0));
    alphabet_list[3].LoadBitmap(IDB_ALPHABET_SMALL_D, RGB(255, 0, 0));
    alphabet_list[4].LoadBitmap(IDB_ALPHABET_SMALL_E, RGB(255, 0, 0));
    alphabet_list[5].LoadBitmap(IDB_ALPHABET_SMALL_F, RGB(255, 0, 0));
    alphabet_list[6].LoadBitmap(IDB_ALPHABET_SMALL_G, RGB(255, 0, 0));
    alphabet_list[7].LoadBitmap(IDB_ALPHABET_SMALL_H, RGB(255, 0, 0));
    alphabet_list[8].LoadBitmap(IDB_ALPHABET_SMALL_I, RGB(255, 0, 0));
    alphabet_list[9].LoadBitmap(IDB_ALPHABET_SMALL_J, RGB(255, 0, 0));
    alphabet_list[10].LoadBitmap(IDB_ALPHABET_SMALL_K, RGB(255, 0, 0));
    alphabet_list[11].LoadBitmap(IDB_ALPHABET_SMALL_L, RGB(255, 0, 0));
    alphabet_list[12].LoadBitmap(IDB_ALPHABET_SMALL_M, RGB(255, 0, 0));
    alphabet_list[13].LoadBitmap(IDB_ALPHABET_SMALL_N, RGB(255, 0, 0));
    alphabet_list[14].LoadBitmap(IDB_ALPHABET_SMALL_O, RGB(255, 0, 0));
    alphabet_list[15].LoadBitmap(IDB_ALPHABET_SMALL_P, RGB(255, 0, 0));
    alphabet_list[16].LoadBitmap(IDB_ALPHABET_SMALL_Q, RGB(255, 0, 0));
    alphabet_list[17].LoadBitmap(IDB_ALPHABET_SMALL_R, RGB(255, 0, 0));
    alphabet_list[18].LoadBitmap(IDB_ALPHABET_SMALL_S, RGB(255, 0, 0));
    alphabet_list[19].LoadBitmap(IDB_ALPHABET_SMALL_T, RGB(255, 0, 0));
    alphabet_list[20].LoadBitmap(IDB_ALPHABET_SMALL_U, RGB(255, 0, 0));
    alphabet_list[21].LoadBitmap(IDB_ALPHABET_SMALL_V, RGB(255, 0, 0));
    alphabet_list[22].LoadBitmap(IDB_ALPHABET_SMALL_W, RGB(255, 0, 0));
    alphabet_list[23].LoadBitmap(IDB_ALPHABET_SMALL_X, RGB(255, 0, 0));
    alphabet_list[24].LoadBitmap(IDB_ALPHABET_SMALL_Y, RGB(255, 0, 0));
    alphabet_list[25].LoadBitmap(IDB_ALPHABET_SMALL_Z, RGB(255, 0, 0));
    alphabet_list[26].LoadBitmap(IDB_ALPHABET_SPACE, RGB(255, 0, 0));
    alphabet_list[27].LoadBitmap(IDB_ALPHABET_DOT, RGB(255, 0, 0));
    alphabet_list[28].LoadBitmap(IDB_ALPHABET_END, RGB(255, 0, 0));
    alphabet_list[29].LoadBitmap(IDB_ALPHABET_DIVISION, RGB(255, 0, 0));
    alphabet_list[30].LoadBitmap(IDB_QUESTION_MARK, RGB(255, 0, 0));
    alphabet_list[31].LoadBitmap(IDB_0, RGB(255, 0, 0));
    alphabet_list[32].LoadBitmap(IDB_1, RGB(255, 0, 0));
    alphabet_list[33].LoadBitmap(IDB_2, RGB(255, 0, 0));
    alphabet_list[34].LoadBitmap(IDB_3, RGB(255, 0, 0));
    alphabet_list[35].LoadBitmap(IDB_4, RGB(255, 0, 0));
    alphabet_list[36].LoadBitmap(IDB_5, RGB(255, 0, 0));
    alphabet_list[37].LoadBitmap(IDB_6, RGB(255, 0, 0));
    alphabet_list[38].LoadBitmap(IDB_7, RGB(255, 0, 0));
    alphabet_list[39].LoadBitmap(IDB_8, RGB(255, 0, 0));
    alphabet_list[40].LoadBitmap(IDB_9, RGB(255, 0, 0));
}

CMovingBitmap* CAlphabet::GetAlphabet(char alphaID)
{
    if (alphaID == 'a') return &alphabet_list[0];
    else if (alphaID == 'b') return &alphabet_list[1];
    else if (alphaID == 'c') return &alphabet_list[2];
    else if (alphaID == 'd') return &alphabet_list[3];
    else if (alphaID == 'e') return &alphabet_list[4];
    else if (alphaID == 'f') return &alphabet_list[5];
    else if (alphaID == 'g') return &alphabet_list[6];
    else if (alphaID == 'h') return &alphabet_list[7];
    else if (alphaID == 'i') return &alphabet_list[8];
    else if (alphaID == 'j') return &alphabet_list[9];
    else if (alphaID == 'k') return &alphabet_list[10];
    else if (alphaID == 'l') return &alphabet_list[11];
    else if (alphaID == 'm') return &alphabet_list[12];
    else if (alphaID == 'n') return &alphabet_list[13];
    else if (alphaID == 'o') return &alphabet_list[14];
    else if (alphaID == 'p') return &alphabet_list[15];
    else if (alphaID == 'q') return &alphabet_list[16];
    else if (alphaID == 'r') return &alphabet_list[17];
    else if (alphaID == 's') return &alphabet_list[18];
    else if (alphaID == 't') return &alphabet_list[19];
    else if (alphaID == 'u') return &alphabet_list[20];
    else if (alphaID == 'v') return &alphabet_list[21];
    else if (alphaID == 'w') return &alphabet_list[22];
    else if (alphaID == 'x') return &alphabet_list[23];
    else if (alphaID == 'y') return &alphabet_list[24];
    else if (alphaID == 'z') return &alphabet_list[25];
    else if (alphaID == ',') return &alphabet_list[27];
    else if (alphaID == '.') return &alphabet_list[28];
    else if (alphaID == '/') return &alphabet_list[29];
    else if (alphaID == '?') return &alphabet_list[30];
    else if (alphaID == '0') return &alphabet_list[31];
    else if (alphaID == '1') return &alphabet_list[32];
    else if (alphaID == '2') return &alphabet_list[33];
    else if (alphaID == '3') return &alphabet_list[34];
    else if (alphaID == '4') return &alphabet_list[35];
    else if (alphaID == '5') return &alphabet_list[36];
    else if (alphaID == '6') return &alphabet_list[37];
    else if (alphaID == '7') return &alphabet_list[38];
    else if (alphaID == '8') return &alphabet_list[39];
    else if (alphaID == '9') return &alphabet_list[40];
    else return &alphabet_list[26];	//¹w³]¦r' '
}
}
