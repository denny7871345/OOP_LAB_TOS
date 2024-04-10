#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "AnimatedCharacter.hpp"
#include "pch.hpp"
#include "Skills.hpp"
#include "Datas.hpp"
#include "Type.hpp"
#include "GiraffeText.hpp"
class Enemy:public AnimatedCharacter{
public:
    void Update();
    Enemy(Type::Element_type type,int life,int attack,int defence,int CD);
    void RoundUp();
    void SetAttackingMethod(std::shared_ptr<AttackSkill> target);
    void AddSkill(std::shared_ptr<Skills> skills){m_SkillList.push_back(skills);}
    Type::Element_type GetType(){return m_type;}
    int GetAtk(){return m_attack;}
    int GetLife(){return m_life;}
    int GetCD(){return m_CD;}
    void AddCD(int num){m_CD += num;}
    int GetDefence(){return m_defence;}
    std::vector<int> Attack(DragingDatas dragingDatas);
    void DealtDamage(int Damage,bool Defence,DragingDatas datas);
private:
    void SkillReset();
    EnemyDatas MyData();
    std::shared_ptr<AttackSkill> m_attackSkill = std::make_shared<AttackSkill>();
    std::vector<std::shared_ptr<Skills>> m_SkillList;
    Type::Element_type m_type;
    int m_firstLife;
    int m_life;
    int m_attack;
    int m_defence;
    int m_CD;
    bool m_hasBeenHit = false;
    std::shared_ptr<GiraffeText> m_text;
};


#endif
