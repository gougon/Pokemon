#pragma once
namespace game_framework
{
class CAlphabet
{
    public:
        CAlphabet();
        ~CAlphabet();
        void LoadBitmap();
        CMovingBitmap* GetAlphabet(char alphaID);
    private:
        CMovingBitmap alphabet_list[41];
};
}