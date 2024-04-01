#include "Skills.hpp"
#include "Member.hpp"
#include "Enchant.hpp"
void Member::Strike(bool onlyone, int damage, bool defence,DragingDatas datas) {
    if(onlyone){
        m_enemies[0]->DealtDamage(damage,defence,datas);
    }else{
        for(int i=0;i<m_enemies.size();i++) m_enemies[i]->DealtDamage(damage,defence,datas);
    }
}

int Boom::StoneBreak(Type::Element_type Lvalue,bool powerup) {
    int count = m_Enchant->StoneBreak(Lvalue);
    m_Enchant->GenerateFall(powerup);
    return count;
}

void StoneTurn::Turn(Type::Element_type Lvalue, Type::Element_type Rvalue, bool powerup) {
    m_Enchant->StoneTurn(Lvalue,Rvalue,0,powerup);
}

bool Skills::SkillsCheck(DragingDatas datas) {
    return true;
}

bool ComboShield::SkillsCheck(DragingDatas datas) {
    if(datas.m_combo > m_num){
        return true;
    } else{
        return false;
    }
}

bool PowerShield::SkillsCheck(DragingDatas datas) {
    //保留
}

bool FirstComboShield::SkillsCheck(DragingDatas datas) {
    if(datas.m_firstCombo == m_num){
        return true;
    }else{
        return false;
    }
}

bool EraseShield::SkillsCheck(DragingDatas datas) {
    m_howmuch -= datas.m_totalErase[Type::FindIndex(m_type)];
    return (m_howmuch <= 0);
}

void EraseShield::ResetHowmuch(int num) {
    m_howmuch = num;
}

std::vector<int> AttackSkill::Attack(EnemyDatas datas) {
    std::vector<int> damages;
    damages.push_back(datas.m_attack);
    return damages;
}

std::vector<int> StrongerSilver::Attack(EnemyDatas datas) {
    std::vector<int> damages;
    float Addition = (1 - (datas.m_life / datas.m_firstLife)) * 10 + 1;
    damages.push_back((int(datas.m_attack * Addition)));
    return damages ;
}

std::vector<int> StrongerGold::Attack(EnemyDatas datas) {
    std::vector<int> damages;
    float Addition = (1 - (datas.m_life / datas.m_firstLife)) * 10 + 1;
    damages.push_back((int(datas.m_attack * Addition)));
    if(Addition >= 8)     damages.push_back((int(datas.m_attack * Addition)));
    return damages;
}

std::vector<int> KeepFight::Attack(EnemyDatas datas) {
    std::vector<int> damages;
    m_times++;
    damages.push_back(datas.m_attack * m_times);
    if(m_times >= 6) damages.push_back(datas.m_attack * m_times);
    return damages;
}

Counter::Counter(int percentage) {
    m_percentage = percentage;
}

std::vector<int> Counter::CounterActivate(EnemyDatas datas) {
    std::vector<int> damage = {};
    if(datas.DealtDamage){
        damage.push_back(datas.m_attack * float(m_percentage * 0.01));
    }else{
        return {};
    }
    return damage;
}