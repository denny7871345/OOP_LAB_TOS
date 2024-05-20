#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "AnimatedCharacter.hpp"
#include "pch.hpp"
#include "Skills.hpp"
#include "Datas.hpp"
#include "Type.hpp"
#include "GiraffeText.hpp"
#include "AbilityStatus.hpp"

class Enemy:public AnimatedCharacter{
public:
    int Conflict(Type::Element_type type,int Damage);
    void SetPos(int x,int y);
    void Update();
    Enemy(Type::Element_type type,int life,int attack,int defence,int CD);
    void RoundUp();
    void SetAttackingMethod(std::shared_ptr<AttackSkill> target);
    void AddSkill(std::shared_ptr<Skills> skills){m_SkillList.push_back(skills);}
    Type::Element_type GetType(){return m_type;}
    int GetAtk(){return m_attack;}
    int GetLife(){return m_life;}
    int GetCD(){return m_CD;}
    void SetDef(float value);
    void SetAtk(float value);
    void AddCD(int num){m_CD += num;}
    int GetDefence(){return m_defence;}
    std::vector<int> Attack(DragingDatas dragingDatas);
    void DealtDamage(int damage,bool Defence,DragingDatas datas);
    void DefReset();
    void AtkReset();
    void AddStatus(const std::shared_ptr<AbilityStatus>& target);
    void DieNow();
    int GetLifePercentage();
    EnemyDatas MyData();
    void SetYpos(float y);
private:
    void SkillReset();
    std::vector<std::shared_ptr<AbilityStatus>> m_status;
    std::shared_ptr<AttackSkill> m_attackSkill = std::make_shared<AttackSkill>();
    std::vector<std::shared_ptr<Skills>> m_SkillList;
    Type::Element_type m_firstType;
    Type::Element_type m_type;
    int m_firstLife;
    int m_life;
    int m_FirstAttack;
    int m_attack;
    int m_FirstDefence;
    int m_defence;
    int m_FirstCD;
    int m_CD;
    bool m_hasBeenHit = false;
    std::shared_ptr<GiraffeText> m_text;
    glm::vec2 m_pos;
};

class EnemyLightGirl: public Enemy{
public:
    EnemyLightGirl();
};

class EnemyLightWerewolf: public Enemy{
public:
    EnemyLightWerewolf();
};

class EnemyLightSlime: public Enemy{
public:
    EnemyLightSlime();
};

class EnemyLightElf: public Enemy{
public:
    EnemyLightElf();
};



#endif
