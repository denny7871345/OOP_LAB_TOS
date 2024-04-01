#include "Enemy.hpp"
#include "Util/Logger.hpp"
Enemy::Enemy(Type::Element_type type, int life, int attack, int defence, int CD):m_type(type),m_life(life),m_attack(attack)
,m_defence(defence),m_CD(CD){}

void Enemy::DealtDamage(int Damage, bool Defence, DragingDatas datas) {
    bool effectedDamage = true;
    for(int i=0;i<m_SkillList.size();i++){
        effectedDamage = (effectedDamage && m_SkillList[i].SkillsCheck(datas));
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
}
