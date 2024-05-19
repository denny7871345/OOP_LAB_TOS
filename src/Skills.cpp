#include "Skills.hpp"
#include "Member.hpp"
#include "Enchant.hpp"
#include "AbilityStatus.hpp"


void Member::Strike(int damage, bool defence,DragingDatas datas) {
    if(datas.onlyone){
        for(int i=0;i<m_enemies.size();i++){
            if(m_enemies[i]->GetLife() > 0){
                m_enemies[i]->DealtDamage(damage,defence,datas);
                return;
            }
        }
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
    LOG_DEBUG("NothingHappens!!");
    return true;
}

bool ComboShield::SkillsCheck(DragingDatas datas) { //V
    LOG_DEBUG("ComboCheck!!");
    if(datas.m_combo >= m_num){
        return true;
    } else{
        return false;
    }
}

bool PowerShield::SkillsCheck(DragingDatas datas) { //V
    LOG_DEBUG("CheckPowerUP!! = {}",datas.m_powerUpBeenErase[Type::FindIndex(datas.m_Attackertype)]);

    return datas.m_powerUpBeenErase[Type::FindIndex(datas.m_Attackertype)];
}

bool FirstComboShield::SkillsCheck(DragingDatas datas) { //V
    if(datas.m_firstCombo == m_num){
        return true;
    }else{
        return false;
    }
}

bool EraseShield::SkillsCheck(DragingDatas datas) { //V
    if(m_firstCount){
        m_howmuch -= (*datas.m_totalErase)[Type::FindIndex(m_type)];
        m_firstCount = false;
    }

    LOG_DEBUG("still need erase {} {} stone!!",m_howmuch,Type::TypeString(m_type));
    return (m_howmuch <= 0);
}

void EraseShield::SkillsRoundReset() { //V
    m_firstCount = true;
}

void EraseShield::ResetHowmuch(int num) {
    m_howmuch = num;
}
//敵技(攻擊)
std::vector<int> AttackSkill::Attack(EnemyDatas enemyDatas,DragingDatas dragingDatas) { //V
    std::vector<int> damages;
    damages.push_back(enemyDatas.m_attack);
    return damages;
}

std::vector<int> DoubleStrike::Attack(EnemyDatas enemyDatas, DragingDatas dragingDatas) {
    std::vector<int> damages;
    damages.push_back(enemyDatas.m_attack);
    damages.push_back(enemyDatas.m_attack);
    return damages;
}

std::vector<int> StrongerSilver::Attack(EnemyDatas enemyDatas,DragingDatas dragingDatas) {  
    std::vector<int> damages;
    float Addition = (1 - (enemyDatas.m_life * 1.0 / enemyDatas.m_firstLife)) * 10 + 1;
    damages.push_back((int(enemyDatas.m_attack * Addition)));
    return damages ;
}

std::vector<int> StrongerGold::Attack(EnemyDatas enemyDatas,DragingDatas dragingDatas) {
    std::vector<int> damages;
    float Addition = (1 - (enemyDatas.m_life * 1.0 / enemyDatas.m_firstLife)) * 10 + 1;
    damages.push_back((int(enemyDatas.m_attack * Addition)));
    if(Addition >= 8)     damages.push_back((int(enemyDatas.m_attack * Addition)));
    return damages;
}

std::vector<int> KeepFight::Attack(EnemyDatas enemyDatas,DragingDatas dragingDatas) { //V
    std::vector<int> damages;
    damages.push_back(enemyDatas.m_attack * m_times);
    if(m_times >= 8) damages.push_back(enemyDatas.m_attack * m_times);
    m_times*= 1.414;
    return damages;
}

PercentageAttacking::PercentageAttacking(float percentage):m_percentage(percentage) {}

std::vector<int> PercentageAttacking::Attack(EnemyDatas enemyDatas, DragingDatas dragingDatas) {
    std::vector<int> damages;
    damages.push_back((*dragingDatas.m_MaxLife) * m_percentage );
    return  damages;
}

Counter::Counter(int percentage) {
    m_percentage = percentage;
}

std::vector<int> Counter::CounterActivate(EnemyDatas enemyDatas) {
    std::vector<int> damage = {};
    if(enemyDatas.DealtDamage){
        damage.push_back(enemyDatas.m_attack * float(m_percentage * 0.01));
    }else{
        return {};
    }
    return damage;
}