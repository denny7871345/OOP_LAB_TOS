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
    bool CheckMatch();
    void ShowEnchant();
    void DoFall();
    bool CheckFall();
    void GenerateFall();
    bool CheckFull();
    void StoneTurn(Type::Element_type LValue,Type::Element_type RValue,int howmany,bool powerup);
    std::vector<int> GetTypeGeneration();
    void SetTypeGeneration(std::vector<int> lists);
private:
    std::vector<std::vector<std::shared_ptr<Stone>>> m_Array;
    state m_state=state::Falling;
    int m_row;
    int m_column;
    glm::vec2 m_StartPos;
    glm::vec2 m_NowPos;
    glm::vec2 m_EndPos;
    std::vector<int> m_TypeGeneration;
};


#endif
