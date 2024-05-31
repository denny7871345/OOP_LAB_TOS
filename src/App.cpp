#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "SelectTeammate.hpp"
#include "GiraffeText.hpp"


void App::Start() {
    m_UI->Start();
    m_enchant->SetSystem(m_battleSystem);
    m_battleSystem->SetEnchant(m_enchant);
    /*m_Giraffe->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/giraffe.png"));
    m_Giraffe->SetZIndex(10);
    m_Giraffe->Start();*/

    m_CurrentState = State::GameSetting;

    addLevelFactory([]() { return std::make_shared<alpha>(); });
    addLevelFactory([]() { return std::make_shared<sample>(); });

    MemberSettingData token = m_battleSystem->CreateMemberData();
    addTeamFactory([](MemberSettingData data) { return std::make_shared<NorthTeam>(data); });
    addTeamFactory([](MemberSettingData data) { return std::make_shared<LoDaTeam>(data); });
    addTeamFactory([](MemberSettingData data) { return std::make_shared<NorthTeam>(data); });
    addTeamFactory([](MemberSettingData data) { return std::make_shared<OlympianTeam>(data); });

}

void App::Setting() {
    m_UI->Update();
    if(m_UI->Complete()){
        m_CurrentState = State::START;
    }
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
    m_UI->Update();
}


void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}

void App::Selecting() {

    m_enchant->Start();
    std::shared_ptr<Team> Teamtoken = SelectedTeam(m_UI->GetTeam());
    m_battleSystem->LoadTeam(Teamtoken);
    std::shared_ptr<Battlefield> token = SelectedLevel(m_UI->GetLevel());
    m_battleSystem->LoadBattlefield(token);
    m_battleSystem->Start();
    m_BG->SetZIndex(-50);
    m_Root.AddChild(m_BG);
    m_Root.AddChild(m_BG2);
    //m_Root.AddChild(m_stone);
    m_CurrentState = State::UPDATE;
}

void App::addTeamFactory(const TeamFactory &factory) {
    m_TeamFactories.push_back(factory);
}

std::shared_ptr<Team> App::SelectedTeam(int index){
    return m_TeamFactories[index](m_battleSystem->CreateMemberData());
}

void App::addLevelFactory(const LevelFactory &factory) {
    m_LevelFactories.push_back(factory);
}

std::shared_ptr<Battlefield> App::SelectedLevel(int index) {
    return m_LevelFactories[index]();
}