#include "Util/SFX.hpp"
#include "Util/BGM.hpp"
#include "pch.hpp"
#include "Util/input.hpp"
#include "Util/Logger.hpp"

class AudioSystem{
public:
    void Start();
    void SetBGM(std::string path);
    void PlayComboSound(int num);
    void PlaySound(std::string path);
    void PlayVictory();
    void PlayLoss();
    void BackToGame();
private:
    Util::BGM m_bgm = Util::BGM("../assets/audio/BATTLE_DUNGEON.wav");

};