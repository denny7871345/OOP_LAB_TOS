#include "BattleSystem.hpp"

void BattleSystem::Start() {
    ResetRound();
}

void BattleSystem::SetCombo(int combo) {
    m_combo = combo;
}

void BattleSystem::AddCombo(int combo) {
    m_combo += combo;
}
void BattleSystem::AddExCombo(int combo) {
    m_exCombo += combo;
}

void BattleSystem::ResetRound() {
    m_nowerase = 0;
    m_firstCombo = 0;
    m_combo = 0;
    m_exCombo = 0;
    m_firstErase = {0,0,0,0,0,0};
    m_totalErase = {0,0,0,0,0,0};
}
bool BattleSystem::DealPair(std::vector<std::shared_ptr<Stone>> Lists) {
    if(Lists[0]->IfAnimationEnds()){
        AddCombo(1);
        m_totalErase[Type::FindIndex(Lists[0]->GetType())] += Lists.size();
        return true;
    }
    for(int i=0;i<Lists.size();i++){
        if(! Lists[i]->IsPlaying()){
            Lists[i]->SetPlaying(true);
        }
    }
    return false;
}
bool BattleSystem::DealFirstPiar(std::vector<std::shared_ptr<Stone>> Lists) {
    if(Lists[0]->IfAnimationEnds()){
        AddCombo(1);
        m_totalErase[Type::FindIndex(Lists[0]->GetType())] += Lists.size();
        m_firstCombo +=1 ;
        m_firstErase[Type::FindIndex(Lists[0]->GetType())] += Lists.size();
        return true;
    }
    for(int i=0;i<Lists.size();i++){
        if(! Lists[i]->IsPlaying()){
            Lists[i]->SetPlaying(true);
        }
    }
    return false;
}

void BattleSystem::ShowData() {
    LOG_DEBUG("first erase:[{},{},{},{},{},{}]",m_firstErase[0],m_firstErase[1],m_firstErase[2],m_firstErase[3],m_firstErase[4],m_firstErase[5]);
    LOG_DEBUG("first erase:[{},{},{},{},{},{}]",m_totalErase[0],m_totalErase[1],m_totalErase[2],m_totalErase[3],m_totalErase[4],m_totalErase[5]);
    LOG_DEBUG("first combo:{}",m_firstCombo);
    LOG_DEBUG("Total combo:{}",m_combo);

}