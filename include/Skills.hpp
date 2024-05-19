#ifndef SKILLS_HPP
#define SKILLS_HPP

#include "Datas.hpp"
#include "Type.hpp"

//敵技(消珠方面)
class Skills{
public:
    virtual bool SkillsCheck(DragingDatas datas);
    virtual void SkillsRoundReset(){}
};

class ComboShield:public Skills{ //v
public:
    explicit ComboShield(int num):m_num(num){}
    bool SkillsCheck(DragingDatas datas) override;
private:
    int m_num;
};

class PowerShield:public Skills{ //v
public:
    bool SkillsCheck(DragingDatas datas) override;
};

class FirstComboShield:public Skills{//V
public:
    explicit FirstComboShield(int num):m_num(num){}
    bool SkillsCheck(DragingDatas datas) override;
private:
    int m_num;
};

class EraseShield:public Skills{ //v
public:
    explicit EraseShield(Type::Element_type type, int howmuch):m_type(type), m_howmuch(howmuch){}
    bool SkillsCheck(DragingDatas datas) override;
    void SkillsRoundReset() override;
    void ResetHowmuch(int num);
private:
    Type::Element_type m_type;
    int m_howmuch;
    bool m_firstCount = true;
};


//敵技(攻擊方面)
class AttackSkill{
public:
    virtual std::vector<int> Attack(EnemyDatas enemyDatas,DragingDatas dragingDatas);
};

class DoubleStrike:public AttackSkill{
public:
    std::vector<int> Attack(EnemyDatas enemyDatas,DragingDatas dragingDatas) override;
};

class StrongerSilver:public AttackSkill{
public:
    std::vector<int> Attack(EnemyDatas enemyDatas,DragingDatas dragingDatas) override;
};

class StrongerGold:public AttackSkill{
public:
    std::vector<int> Attack(EnemyDatas enemyDatas,DragingDatas dragingDatas) override;
};

class KeepFight:public AttackSkill{
public:
    std::vector<int> Attack(EnemyDatas enemyDatas,DragingDatas dragingDatas) override;
private:
    float m_times=1;
};

class PercentageAttacking:public AttackSkill{
public:
    PercentageAttacking(float percentage);
    std::vector<int> Attack(EnemyDatas enemyDatas,DragingDatas dragingDatas) override;
private:
    float m_percentage;
};

//敵技(反擊)
class Counter{
public:
    Counter(int percentage);
    virtual std::vector<int> CounterActivate(EnemyDatas datas);
private:
    int m_percentage;
};

#endif
