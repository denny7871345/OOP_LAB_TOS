#include "AudioSystem.hpp"

void AudioSystem::PlayComboSound(int num) {
    static auto SFX1 = Util::SFX("../assets/audio/Combo/combo1.wav");
    static auto SFX2 = Util::SFX("../assets/audio/Combo/combo2.wav");
    static auto SFX3= Util::SFX("../assets/audio/Combo/combo3.wav");
    static auto SFX4 = Util::SFX("../assets/audio/Combo/combo4.wav");
    static auto SFX5 = Util::SFX("../assets/audio/Combo/combo5.wav");
    static auto SFX6 = Util::SFX("../assets/audio/Combo/combo6.wav");
    static auto SFX7 = Util::SFX("../assets/audio/Combo/combo7.wav");
    static auto SFX8 = Util::SFX("../assets/audio/Combo/combo8.wav");
    static auto SFX9 = Util::SFX("../assets/audio/Combo/combo9.wav");
    static auto SFX10 = Util::SFX("../assets/audio/Combo/combo10.wav");
    switch (num) {
    case 1:
        SFX1.Play();
        break;
    case 2:
        SFX2.Play();
        break;
    case 3:
        SFX3.Play();
        break;
    case 4:
        SFX4.Play();
        break;
    case 5:
        SFX5.Play();
        break;
    case 6:
        SFX6.Play();
        break;
    case 7:
        SFX7.Play();
        break;
    case 8:
        SFX8.Play();
        break;
    case 9:
        SFX9.Play();
        break;
    default:
        SFX10.Play();
        break;
    }

}

void AudioSystem::PlaySound(std::string path) {
    auto SFX = Util::SFX("../assets/audio/Combo/combo" + path + ".wav");
    SFX.Play();
}

void AudioSystem::Start() {
    m_bgm.Play();
}

void AudioSystem::SetBGM(std::string path) {
    m_bgm.LoadMedia(path);
}