#include "App.hpp"
#include "Util/BGM.hpp"
#include "Core/Context.hpp"


int main(int, char **) {
    auto context = Core::Context::GetInstance();
    App app;
    auto bgm = Util::BGM("../assets/audio/MAIN_THEME_NIGHT_OLD.wav");
    while (!context->GetExit()) {
        switch (app.GetCurrentState()) {
        case App::State::START:
            app.Start();
            bgm.Play();
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
