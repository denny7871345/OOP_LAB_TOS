#ifndef DATAS_HPP
#define DATAS_HPP

#include <utility>
#include "pch.hpp"
#include "Type.hpp"
class Enchant;
class AbilityStatus;
class BattleSystem;
class Skills;
class AttackSkill;

typedef void (BattleSystem::*FuncPtr)(int);
struct DragingDatas{
    bool onlyone;
    std::shared_ptr<std::vector<int>> m_totalErase;
    std::shared_ptr<std::vector<int>> m_firstErase;
    std::vector<bool>m_powerUpBeenErase={false,false,false,false,false,false};
    std::vector<bool>m_eraseMoreThan5 = {false,false,false,false,false,false};
    std::shared_ptr<int> m_MaxLife;
    int m_combo = 0;
    int m_exCombo = 0;
    int m_firstCombo = 0;
    Type::Element_type m_Attackertype = Type::Element_type::Heart;
};

struct EnemyDatas{
    int m_firstLife;
    int m_life;
    int m_attack;
    int m_defence;
    int m_CD;
    bool DealtDamage;
    std::vector<std::shared_ptr<Skills>> m_SkillList;
    std::shared_ptr<AttackSkill> m_attackSkill;
};

struct MemberSettingData{

    std::shared_ptr<FuncPtr> GetDamage = nullptr;
    std::shared_ptr<std::vector<std::shared_ptr<AbilityStatus>>> m_status;
    std::shared_ptr<Enchant> m_Enchant;
    std::shared_ptr<std::vector<float>> m_FirstAddition;
    std::shared_ptr<std::vector<float>> m_FirstRaceAddition;
    std::shared_ptr<std::vector<float>> m_ElementAddition;
    std::shared_ptr<std::vector<float>> m_RaceAddition;
    std::shared_ptr<float> m_dealtDamageDecrease;
    std::shared_ptr<float> m_addCombo;
    std::shared_ptr<std::vector<int>> m_totalErase;
    std::shared_ptr<std::vector<int>> m_firstErase;
    std::shared_ptr<int> m_life;
    std::shared_ptr<int> m_MaxLife;
};

#endif
