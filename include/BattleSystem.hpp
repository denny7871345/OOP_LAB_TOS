#ifndef BATTLESYSTEM_HPP
#define BATTLESYSTEM_HPP

#include "Stone.hpp"
#include "Member.hpp"

class Enchant;

class BattleSystem {
public:

private:
    std::vector<int> m_totalErase={0,0,0,0,0,0};
    std::vector<int> m_firstErase={0,0,0,0,0,0};
    std::shared_ptr<Enchant> m_Enchant;
    std::vector<std::shared_ptr<Member>> m_Members;
    int m_life;
    int m_MaxLife;
    int m_combo;
    int m_firstCombo;
};

#endif
