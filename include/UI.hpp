//
// Created by fungp on 2024/5/31.
//
#include "Battlefield.hpp"
#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP


class Choice : public Util::GameObject{
public:
    Choice(std::string path,int index,int total);
    void Update();
protected:
    int m_index;
    int m_total;
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
private:
    std::vector<std::shared_ptr<Choice>> m_levels;
    std::vector<std::shared_ptr<Choice>> m_Teams;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_UI_HPP
