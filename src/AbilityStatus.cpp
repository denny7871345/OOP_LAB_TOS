#include "AbilityStatus.hpp"
#include "Enemy.hpp"
#include "Member.hpp"

AbilityStatus::AbilityStatus(AbilityType type, int CountDown) {
    m_abilityType = type;
    m_countDown = CountDown;
}

bool AbilityStatus::RoundUp() {
    if(m_countDown == -1){
        return false;
    }else{
        m_countDown --;
        if(m_countDown == 0){
            return true;
        } else{
            return false;
        }
    }
}

PowerRaise::PowerRaise(std::shared_ptr<std::vector<float>> target, Type::Element_type type, float increase, int CountDown):
        m_Addition(target),m_type(type),m_Increase(increase),AbilityStatus(AbilityType::DamageSettle,CountDown) {

}

void PowerRaise::Trigger() {
        (*m_Addition)[Type::FindIndex(m_type)] *= m_Increase;
}


DamageDecrease::DamageDecrease(std::shared_ptr<float> target, float Decrease, int CountDown):
      AbilityStatus(AbilityType::DealtDamageEffect,CountDown),m_DamageDecrease(target),m_value(Decrease){

}

void DamageDecrease::Trigger() {
    *m_DamageDecrease = m_value;
}

ShiledBreak::ShiledBreak(std::shared_ptr<Enemy> target, float value, int CountDown):
      AbilityStatus(AbilityType::EnemyValueChange,CountDown),m_enemy(target),m_value(value) {
}

void ShiledBreak::Trigger() {
    m_enemy->SetDef(m_value);
}

void ShiledBreak::Reset() {
    m_enemy->DefReset();
}

AbilityType LeaderSkill::GetType() {
    return m_abilityType;
}

PowerUp::PowerUp(std::shared_ptr<std::vector<float>> target, Type::Element_type type, float increase):m_Addition(target),m_type(type),m_increase(increase) {
    m_abilityType = AbilityType::Setting;
}

void PowerUp::Skill() {
    (*m_Addition)[Type::FindIndex(m_type)] *= m_increase;
}

RaceUp::RaceUp(std::shared_ptr<std::vector<float>> target, Type::Race_type type, float increase):m_Addition(target),m_type(type),m_increase(increase) {
    m_abilityType = AbilityType::Setting;
}

void RaceUp::Skill() {
    (*m_Addition)[Type::FindIndex(m_type)] *= m_increase;
}

Launch::Launch(std::vector<std::shared_ptr<Member>> target, float times):m_team(target),m_times(times) {
    m_abilityType = AbilityType::TurnEnd;
}
void Launch::Skill() {
    int damage = m_team[0]->GetAtk() * m_times;
    DragingDatas token;
    token.m_Attackertype = Type::Element_type::Heart;
    m_team[0]->Strike(false,damage, true,token);
}

ComboUp::ComboUp(std::shared_ptr<float> target, float howmuch):m_increase(howmuch),m_addCombo(target) {
    m_abilityType = AbilityType::Setting;
}

void ComboUp::Skill() {
    *(m_addCombo) += m_increase;
}