//
// Created by fungp on 2024/5/31.
//
#include "UI.hpp"
#include "Enchant.hpp"
const int ImgSize = 140;
Choice::Choice(std::string path, int index) {
    SetZIndex(20);
    m_index = index;
    SetDrawable(
        std::make_shared<Util::Image>(path));
    m_Transform.translation = {0,400-ImgSize*(index)};
    m_Transform.scale = {0.6,0.6};
}

bool Choice::IsClicked() {
    auto cursorPos = Util::Input::GetCursorPosition();
    if(cursorPos.y < 450-ImgSize*(m_index) && cursorPos.y > 350-ImgSize*(m_index) && cursorPos.x > -200 && cursorPos.x < 200){
        LOG_DEBUG("U click {} choice!",m_index);
        return true;
    }
    return false;
}

void Choice::Update() {
    this->Draw();



}
void UI::Start() {
    std::shared_ptr<Choice> m_test = std::make_shared<Choice>("../assets/sprites/Teams/BeastTeam.png",1);
    std::shared_ptr<Choice> m_test1 = std::make_shared<Choice>("../assets/sprites/Teams/LoDaTeam.png",2);
    std::shared_ptr<Choice> m_test2 = std::make_shared<Choice>("../assets/sprites/Teams/NorthTeam.png",3);
    std::shared_ptr<Choice> m_test3 = std::make_shared<Choice>("../assets/sprites/Teams/OlympianTeam.png",4);
    m_Teams.push_back(m_test);
    m_Teams.push_back(m_test1);
    m_Teams.push_back(m_test2);
    m_Teams.push_back(m_test3);
    m_test = std::make_shared<Choice>("../assets/sprites/Levels/alpha.png",1);
    m_test1 = std::make_shared<Choice>("../assets/sprites/Levels/Sample.png",2);
    m_levels.push_back(m_test);
    m_levels.push_back(m_test1);
    LOG_DEBUG("Choose the Battlefield.");
}

void UI::Update() {
    switch (m_state) {
    case State::Level:
        for(int i=0;i<2;i++){
            m_levels[i]->Update();
        }
        break;
    case State::Team:
        for(int i=0;i<4;i++){
            m_Teams[i]->Update();
        }
        break;
    }
    m_button->Update();

    if (Util::Input::IsKeyDown(Util::Keycode::E)) {
            if(m_state == State::Level){
                for(int i=0;i<2;i++) {
                    if (m_levels[i]->IsClicked()) {
                        m_LevelIndex = i;
                    }
                }
            }else if(m_state == State::Team){
                for(int i=0;i<4;i++) {
                    if (m_Teams[i]->IsClicked()) {
                        m_TeamIndex = i;
                    }
                }
            }
    }

    if (Util::Input::IsKeyUp(Util::Keycode::E)) {
        if(m_button->IsClicked()){
            if(m_state == State::Level){
                if(m_LevelIndex != -1){
                    NextPage();
                }else{
                    LOG_DEBUG("Please select your battlefield!!!!");
                }
            }else if(m_state == State::Team){
                if(m_TeamIndex != -1){
                    NextPage();
                }else{
                    LOG_DEBUG("Please select your team!!!!");
                }
            }
        }
    }
}

void UI::NextPage() {
    if(m_state == State::Level){
        m_state = State::Team;
        LOG_DEBUG("Good,Then choose your Team");
    }else if(m_state == State::Team){
        for(int i=0;i<2;i++){
            m_levels[i]->SetVisible(false);
        }
        for(int i=0;i<4;i++){
            m_Teams[i]->SetVisible(false);
        }
        m_button->SetVisible(false);
        SetVisible(false);
        m_done = true;
        LOG_DEBUG("you chose {} Level and {} Team",m_LevelIndex+1, m_TeamIndex+1);
    }
}

bool UI::Complete() {
    return m_done;
}

Button::Button() {
    SetZIndex(20);
    m_Transform.scale = {0.8,0.8};
    std::string path = "../assets/sprites/CheckButton0.png";
    SetDrawable( std::make_shared<Util::Image>(path) );
    m_Transform.translation = {150,-300};
}

void Button::Update() {
    auto cursorPos = Util::Input::GetCursorPosition();

    if (Util::Input::IsKeyDown(Util::Keycode::E)) {
        if(cursorPos.y < -275 && cursorPos.y > -325 && cursorPos.x > 75 && cursorPos.x < 225){
            m_click = true;
        }
    }
    if (Util::Input::IsKeyUp(Util::Keycode::E)) {
        m_click = false;
    }

    if(m_click){
        std::string path = "../assets/sprites/CheckButton1.png";
        SetDrawable( std::make_shared<Util::Image>(path) );
    }else{
        std::string path = "../assets/sprites/CheckButton0.png";
        SetDrawable( std::make_shared<Util::Image>(path) );
    }


    this->Draw();
}

bool Button::IsClicked() {
    auto cursorPos = Util::Input::GetCursorPosition();
    if(cursorPos.y < -275 && cursorPos.y > -325 && cursorPos.x > 75 && cursorPos.x < 225){
        return true;
    }
    return false;
}

bool Button::GetClick() {
    return m_click;
}

int UI::GetTeam() {
    return m_TeamIndex;
}

int UI::GetLevel() {
    return m_LevelIndex;
}