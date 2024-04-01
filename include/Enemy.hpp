#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "pch.hpp"
#include "Skills.hpp"
#include "Datas.hpp"
#include "Type.hpp"

class Enemy{
public:
    Enemy(Type::Element_type type,int life,int attack,int defence,int CD);
    void AddSkill(std::shared_ptr<Skills> skills){m_SkillList.push_back(skills);}
    Type::Element_type GetType(){return m_type;}
    int GetAtk(){return m_attack;}
    int GetLife(){return m_life;}
    int GetCD(){return m_CD;}
    void AddCD(int num){m_CD += num;}
    int GetDefence(){return m_defence;}
    void DealtDamage(int Damage,bool Defence,DragingDatas datas);
private:
    std::vector<std::shared_ptr<Skills>> m_SkillList;
    bool EffectiveDamage;
    Type::Element_type m_type;
    int m_firstLife;
    int m_life;
    int m_attack;
    int m_defence;
    int m_CD;
};


#endif
