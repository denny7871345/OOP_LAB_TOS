#ifndef SKILLS_HPP
#define SKILLS_HPP

#include "Datas.hpp"
#include "Type.hpp"




//敵技(轉珠方面)
class Skills{
public:
    virtual bool SkillsCheck(DragingDatas datas);
};

class ComboShield:public Skills{
public:
    explicit ComboShield(int num):m_num(num){}
    bool SkillsCheck(DragingDatas datas) override;
private:
    int m_num;
};

class PowerShield:public Skills{
public:
    bool SkillsCheck(DragingDatas datas) override;
};

class FirstComboShield:public Skills{
public:
    explicit FirstComboShield(int num):m_num(num){}
    bool SkillsCheck(DragingDatas datas) override;
private:
    int m_num;
};

class EraseShield:public Skills{
public:
    explicit EraseShield(Type::Element_type type, int howmuch):m_type(type), m_howmuch(howmuch){}
    bool SkillsCheck(DragingDatas datas) override;
    void ResetHowmuch(int num);
private:
    Type::Element_type m_type;
    int m_howmuch;
};
//敵技(攻擊方面)
class AttackSkill{
public:
    virtual std::vector<int> Attack(EnemyDatas datas);
};

class StrongerSilver:public AttackSkill{
public:
    std::vector<int> Attack(EnemyDatas datas) override;
};

class StrongerGold:public AttackSkill{
public:
    std::vector<int> Attack(EnemyDatas datas) override;
};

class KeepFight:public AttackSkill{
public:
    std::vector<int> Attack(EnemyDatas datas) override;
private:
    int m_times=0;
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
