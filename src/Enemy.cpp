#include "Enemy.hpp"
#include "Util/Logger.hpp"
Enemy::Enemy(Type::Element_type type, int life, int attack, int defence, int CD):m_type(type),m_life(life),m_attack(attack)
,m_defence(defence),m_CD(CD){
    m_firstLife = m_life;
}

void Enemy::DealtDamage(int Damage, bool Defence, DragingDatas datas) {
    if(Damage ==0)
        return;

    bool effectedDamage = true;
    for(int i=0;i<m_SkillList.size();i++){
        effectedDamage = (effectedDamage && m_SkillList[i]->SkillsCheck(datas));
    }
    if(effectedDamage){
        if(Defence){
            if(Damage > m_defence){
                LOG_DEBUG("Enemy has dealt {} damage left.",Damage-m_defence);
                m_life -= (Damage-m_defence);
            }else{
                LOG_DEBUG("Enemy has dealt 1 damage left.");
                m_life -= 1;
            }
        }else{
            LOG_DEBUG("Enemy has dealt {} damage left.",Damage);
            m_life -= Damage;
        }
    }else{
        m_life -= 1;
    }
    m_hasBeenHit = true;
}

void Enemy::RoundUp() {
    m_hasBeenHit = false;
    SkillReset();
}

void Enemy::SkillReset() {
    for(int i=0;i<m_SkillList.size();i++) m_SkillList[i]->SkillsRoundReset();
}

EnemyDatas Enemy::MyData() {
    EnemyDatas token{m_firstLife,m_life,m_attack,m_defence,m_CD,m_hasBeenHit};
    return token;
}

std::vector<int> Enemy::Attack( DragingDatas Datas) {
    std::vector<int> token = m_attackSkill->Attack(MyData(),Datas);
    return token;
}

void Enemy::SetAttackingMethod(std::shared_ptr<AttackSkill> target) {
    m_attackSkill = target;
}