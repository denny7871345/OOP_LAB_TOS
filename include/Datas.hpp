#ifndef DATAS_HPP
#define DATAS_HPP

#include <utility>
#include "pch.hpp"
#include "Type.hpp"

struct DragingDatas{
    std::vector<int> m_totalErase={0,0,0,0,0,0};
    std::vector<int> m_firstErase={0,0,0,0,0,0};
    std::vector<bool>m_powerUpBeenErase={false,false,false,false,false,false};
    int m_combo;
    int m_exCombo;
    int m_firstCombo;
    Type::Element_type m_Attackertype;
};

struct EnemyDatas{
    int m_firstLife;
    int m_life;
    int m_attack;
    int m_defence;
    int m_CD;
    bool DealtDamage;
};



#endif
