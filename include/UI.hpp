//
// Created by fungp on 2024/5/31.
//
#include "Battlefield.hpp"

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP


class Choice : public Util::GameObject{
public:
    Choice(std::string path,int index);
    bool IsClicked();
    void Update();
protected:
    int m_index;
};

class Button : public Util::GameObject{
public:
    Button();
    bool IsClicked();
    bool GetClick();
    void Update();
private:
    bool m_click = false;
};


class UI : public Util::GameObject{
    enum State{
        Level,
        Team
    };
public:
    void Start();
    void Update();
    void NextPage();
    bool Complete();
    int GetLevel();
    int GetTeam();
private:
    std::vector<std::shared_ptr<Choice>> m_levels;
    std::vector<std::shared_ptr<Choice>> m_Teams;
    State m_state = State::Level;
    std::shared_ptr<Button> m_button = std::make_shared<Button>();
    bool m_done = false;
    int m_LevelIndex = -1;
    int m_TeamIndex = -1;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
