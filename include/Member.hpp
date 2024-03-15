#ifndef MEMBER_HPP
#define MEMBER_HPP
#include <utility>
#include "Stone.hpp"
class Enchant;
class Enemy;
class Member {
public:
    virtual void Skill()=0;
    Type::Element_type GetType(){return m_type;}
    int GetAtk(){return m_attack;}
    int GetLife(){return m_life;}
    int GetHeal(){return m_heal;}
    Member(Type::Element_type type,int attack,int life,int heal):m_type(type),m_attack(attack),m_life(life),m_heal(heal){};
private:
    std::shared_ptr<Enemy> m_enemy;
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


//skill
class Boom{
public:
    explicit Boom(std::shared_ptr<Enchant> target):m_Enchant(std::move(target)){};
    int StoneBreak(Type::Element_type Lvalue,bool powerup);
private:
    std::shared_ptr<Enchant> m_Enchant;
};

class DealDamage{
public:
    void Strike(std::shared_ptr<Enemy> target,int damage);
};

class StoneTurn{
public:
    explicit StoneTurn(std::shared_ptr<Enchant> target):m_Enchant(std::move(target)){};
    void Turn(Type::Element_type Lvalue,Type::Element_type Rvalue,bool powerup);
private:
    std::shared_ptr<Enchant> m_Enchant;
};

//Charctor
class Mori:public Member,Boom,DealDamage{
public:
    explicit Mori(std::shared_ptr<Enchant> target): Member(Type::Element_type::Water,1155,1881,384),
          Boom(std::move(target)){};
    void Skill() override{
        StoneBreak(Type::Element_type::Grass,true);
    }
};

class Sean:public Member,Boom,DealDamage{
public:
    explicit Sean(std::shared_ptr<Enchant> target): Member(Type::Element_type::Fire,1107,1980,384),
          Boom(std::move(target)){};
    void Skill() override{
        StoneBreak(Type::Element_type::Water,true);
    }
};

class WaterSlime:public Member,StoneTurn{
public:
    explicit WaterSlime(std::shared_ptr<Enchant> target): Member(Type::Element_type::Water,1107,1980,384),
          StoneTurn(std::move(target)){};
    void Skill() override{
        Turn(Type::Element_type::Fire,Type::Element_type::Heart,true);
    }
};
#endif
