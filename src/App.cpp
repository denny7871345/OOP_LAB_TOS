#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "GiraffeText.hpp"

void App::Start() {
    LOG_TRACE("Start");
    //m_enchant->SetSystem(m_battleSystem);
    m_enchant->Start();


    /*m_Giraffe->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/giraffe.png"));
    m_Giraffe->SetZIndex(10);
    m_Giraffe->Start();*/

    m_BG->SetZIndex(-50);
    m_Root.AddChild(m_BG);
    //m_Root.AddChild(m_stone);
    m_CurrentState = State::UPDATE;
}

void App::Update() {
    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)) {
        auto cursorPos = Util::Input::GetCursorPosition();
        LOG_DEBUG("Mouse clicking! x:{}, y{}", (cursorPos.x + 225 ) / 75, (cursorPos.y + 350) / 78);
    }
    /*if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_RB)) {
        LOG_DEBUG("Right button up");
    }*/
    /*if (Util::Input::IfScroll()) {
        auto delta = Util::Input::GetScrollDistance();
        LOG_DEBUG("Scrolling: x: {}, y: {}", delta.x, delta.y);
    }*/
    /*if (Util::Input::IsMouseMoving()) {
        //LOG_DEBUG("Mouse moving! x:{}, y{}", cursorPos.x, cursorPos.y);
    }*/

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    /*if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
        LOG_DEBUG("B Pressed. Setting the cursor to (0, 0).");
        Util::Input::SetCursorPosition({0.0F, 0.0F});
        LOG_DEBUG("Cursor set to {}.", glm::to_string(Util::Input::GetCursorPosition()));
    }*/
   // m_Giraffe->Update();
    m_enchant->Update();
    m_Root.Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
