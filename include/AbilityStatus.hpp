#ifndef ABILITYSTATUS_HPP
#define ABILITYSTATUS_HPP

#include "Util/GameObject.hpp"
#include "Skills.hpp"


class Enemy;
class Member;

enum AbilityType{
    DamageSettle,
    EnemyValueChange,
    EraseOfStone,
    DealtDamageEffect,
    Dragging,
    Setting,
    TurnEnd,
    Checking
};

//附加狀態
class AbilityStatus{
public:
    AbilityStatus(AbilityType type,int CountDown);
    virtual void Trigger() = 0;
    virtual void Reset(){};
    bool RoundUp();
protected:
    AbilityType m_abilityType;
    int m_countDown;
};

class PowerRaise: public AbilityStatus{
public:
    PowerRaise(std::shared_ptr<std::vector<float>> target, Type::Element_type type, float increase, int CountDown);
    virtual void Trigger() override;
protected:
    std::shared_ptr<std::vector<float>> m_Addition;
    Type::Element_type m_type;
    float m_Increase;
};

class DamageDecrease: public AbilityStatus{
public:
    DamageDecrease(std::shared_ptr<float> target, float Decrease, int CountDown);
    virtual void Trigger() override;
private:
    std::shared_ptr<float> m_DamageDecrease;
    float m_value;
};

class ShiledBreak: public AbilityStatus{
public:
    ShiledBreak(std::shared_ptr<Enemy> target,float value, int CountDown);
    virtual void Trigger() override;
    virtual void Reset() override;
private:
    std::shared_ptr<Enemy> m_enemy;
    float m_value;
};

//隊長技能
class LeaderSkill{
public:
    virtual void Skill() = 0;
    AbilityType GetType();
protected:
    AbilityType m_abilityType;
};

class PowerUp: public LeaderSkill{
public:
    PowerUp(std::shared_ptr<std::vector<float>> target ,Type::Element_type type,float increase);
    virtual void Skill() override;
private:
    std::shared_ptr<std::vector<float>> m_Addition;
    Type::Element_type m_type;
    float m_increase;
};

class RaceUp: public LeaderSkill{
public:
    RaceUp(std::shared_ptr<std::vector<float>> target ,Type::Race_type type,float increase);
    virtual void Skill() override;
private:
    std::shared_ptr<std::vector<float>> m_Addition;
    Type::Race_type m_type;
    float m_increase;
};

class Launch:public LeaderSkill{
public:
    Launch(std::vector<std::shared_ptr<Member>> target ,float times);
    virtual void Skill() override;
private:
    std::vector<std::shared_ptr<Member>> m_team;
    float m_times;
};

class ComboUp: public LeaderSkill{
public:
    ComboUp(std::shared_ptr<float> target,float howmuch);
    virtual void Skill() override;
private:
    std::shared_ptr<float> m_addCombo;
    float m_increase;
};
#endif
