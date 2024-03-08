#ifndef MEMBER_HPP
#define MEMBER_HPP
#include <utility>
#include "Enchant.hpp"
class Member {
public:
    virtual void skill(std::shared_ptr<Enchant> target);
    Member(Type::Element_type type,int attack,int life,int heal):m_type(type),m_attack(attack),m_life(life),m_heal(heal){};
private:
    Type::Element_type m_type;
    int m_attack;
    int m_life;
    int m_heal;
};

class Enemy {
public:
    virtual bool Skills(std::shared_ptr<Enchant> target);
private:
    int m_attack;
    int m_defence;
    int CD;
};
#endif
