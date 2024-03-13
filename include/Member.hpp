#ifndef MEMBER_HPP
#define MEMBER_HPP
#include <utility>
#include "Stone.hpp"
class Enchant;

class Member {
public:
    virtual void Skill()=0;
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

class Boom{
public:
    explicit Boom(std::shared_ptr<Enchant> target):m_Enchant(std::move(target)){};
    int StoneBreak(Type::Element_type Lvalue,bool powerup);
private:
    std::shared_ptr<Enchant> m_Enchant;
};

class Mori:public Member,Boom{
public:
    explicit Mori(std::shared_ptr<Enchant> target): Member(Type::Element_type::Water,1881,1155,384),
          Boom(std::move(target)){};
    void Skill() override{
        StoneBreak(Type::Element_type::Fire,true);
    }
};
#endif
