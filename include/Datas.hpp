#ifndef DATAS_HPP
#define DATAS_HPP

#include <utility>
#include "pch.hpp"
#include "Type.hpp"
class Enchant;

struct DragingDatas{
    std::vector<int> m_totalErase={0,0,0,0,0,0};
    std::vector<int> m_firstErase={0,0,0,0,0,0};
    std::vector<bool>m_powerUpBeenErase={false,false,false,false,false,false};
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
};

struct MemberSettingData{
    std::shared_ptr<Enchant> m_Enchant;
    std::shared_ptr<std::vector<float>> m_FirstAddition;
    std::shared_ptr<std::vector<float>> m_FirstRaceAddition;
    std::shared_ptr<float> m_dealtDamageDecrease = std::make_shared<float>(0.0f);
    std::shared_ptr<float> m_addCombo;

};

#endif
