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
    Member(Type::Element_type type,int attack,int life,int heal,std::shared_ptr<Enchant> Enchant):m_type(type),m_attack(attack),m_life(life),m_heal(heal),m_Enchant(Enchant){};
private:
    std::shared_ptr<Enchant> m_Enchant;
    std::vector<std::shared_ptr<Member>> m_team;
    std::shared_ptr<Enemy> m_enemy;
    Type::Element_type m_type;
    int m_attack;
    int m_life;
    int m_heal;
};

class Enemy{
public:
    Enemy(Type::Element_type type,int life,int attack,int defence,int CD);
    Type::Element_type GetType(){return m_type;}
    int GetAtk(){return m_attack;}
    int GetLife(){return m_life;}
    int GetCD(){return m_CD;}
    int GetDefence(){return m_defence;}
    void DealtDamage(int Damage,bool Defence);
    virtual bool Skills(){return true;}
private:
    bool EffectiveDamage;
    Type::Element_type m_type;
    int m_life;
    int m_attack;
    int m_defence;
    int m_CD;
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
    void Strike(std::shared_ptr<Enemy> target,int damage,bool defence);
};

class StoneTurn{
public:
    explicit StoneTurn(std::shared_ptr<Enchant> target):m_Enchant(std::move(target)){};
    void Turn(Type::Element_type Lvalue,Type::Element_type Rvalue,bool powerup);
private:
    std::shared_ptr<Enchant> m_Enchant;
};

class Dio{
    Dio(std::shared_ptr<Enchant> target):m_Enchant(std::move(target)){};
    void TheWorld(int seconds);
private:
    std::shared_ptr<Enchant> m_Enchant;
};


//Charctor
class Mori:public Member,Boom,DealDamage{
public:
    explicit Mori(std::shared_ptr<Enchant> target): Member(Type::Element_type::Water,1155,1881,423,target),
          Boom(std::move(target)){};
    void Skill() override{
        StoneBreak(Type::Element_type::Grass,true);
    }
};

class Sean:public Member,Boom,DealDamage{
public:
    explicit Sean(std::shared_ptr<Enchant> target): Member(Type::Element_type::Fire,1107,1980,384,target),
          Boom(std::move(target)){};
    void Skill() override{
        StoneBreak(Type::Element_type::Water,true);
    }
};

class WaterSlime:public Member,StoneTurn{
public:
    explicit WaterSlime(std::shared_ptr<Enchant> target): Member(Type::Element_type::Water,1107,1980,384,target),
          StoneTurn(std::move(target)){};
    void Skill() override{
        Turn(Type::Element_type::Fire,Type::Element_type::Heart,true);
    }
};
#endif
