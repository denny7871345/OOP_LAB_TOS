#ifndef ENCHANT_HPP
#define ENCHANT_HPP

#include "Stone.hpp"
#include "Util/GameObject.hpp"
class Enchant:public Util::GameObject{
public:
    enum class state{
        Falling,
        Checking,
        Keeping,
        Dragging,
        Moving
    };
    void Update();
    void Start();
    void Change(glm::vec2 pos1,glm::vec2 pos2);


private:
    std::vector<std::vector<std::shared_ptr<Stone>>> m_Array;
    state m_state=state::Falling;
    glm::vec2 m_StartPos;
    glm::vec2 m_NowPos;
    glm::vec2 m_EndPos;
};


#endif
