#include "App.hpp"
#include "Util/BGM.hpp"
#include "Core/Context.hpp"


int main(int, char **) {
    auto context = Core::Context::GetInstance();
    App app;
    app.Start();
    Util::BGM bgm = Util::BGM("../assets/audio/BATTLE_DUNGEON.wav");
    static auto start = Util::SFX("../assets/audio/gameStart.wav");
    bgm.LoadMedia("../assets/audio/MAIN_THEME_NIGHT_OLD.wav");
    //"../assets/audio/MAIN_THEME_NIGHT_OLD.wav"
    bgm.Play();
    while (!context->GetExit()) {
        switch (app.GetCurrentState()) {
        case App::State::GameSetting:
            app.Setting();

            break;
        case App::State::START:
            bgm.FadeOut(3000);
            app.Selecting();
            start.Play();
            break;

        case App::State::UPDATE:


            app.Update();
            break;

        case App::State::END:
            app.End();
            context->SetExit(true);
            break;
        }
        context->Update();
    }
    return 0;
}
