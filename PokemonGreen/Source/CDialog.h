#pragma once
#include <string>
#include "CAlphabet.h"
enum alphaID
{
    a, //0
    b, //1
    c, //2
    d, //3
    e, //4
    f, //5
    g, //6
    h, //7
    i, //8
    j, //9
    k, //10
    l, //11
    m, //12
    n, //13
    o, //14
    p, //15
    q, //16
    r, //17
    s, //18
    t, //19
    u, //20
    v, //21
    w, //22
    x, //23
    y, //24
    z, //25
};
using namespace std;
namespace game_framework
{
class CDialog
{
    public:
        CDialog();
        void SetText(string inputstr);
        void InitDialog(char);
        void OnMove();
        void OnShow();
    private:
        CMovingBitmap screen;
        CAnimation cursor;
        string showString;
        CAlphabet showAlphabet;
};
}