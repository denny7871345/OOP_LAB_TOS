#include "Member.hpp"
#include "Enchant.hpp"

int Boom::StoneBreak(Type::Element_type Lvalue,bool powerup) {
    int count = m_Enchant->StoneBreak(Lvalue);
    m_Enchant->GenerateFall(powerup);
    return count;
}

void StoneTurn::Turn(Type::Element_type Lvalue, Type::Element_type Rvalue, bool powerup) {
    m_Enchant->StoneTurn(Lvalue,Rvalue,0,powerup);
}

void DealDamage::Strike(std::shared_ptr<Enemy> target, int damage,bool defence) {
    target-> DealtDamage(damage,defence);
}

Enemy::Enemy(Type::Element_type type, int life, int attack, int defence, int CD):m_type(type),m_life(life),m_attack(attack),m_defence(defence),m_CD(CD){

}

void Enemy::DealtDamage(int Damage, bool Defence) {
    if(Skills()){
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
        LOG_DEBUG("Enemy has dealt 1 damage left.");
        m_life -= 1;
    }
}

void Dio::TheWorld(int seconds) {  //排珠系統先不要動
    m_Enchant->SetDraggingTime(seconds);
    m_Enchant->SetState(Enchant::state::Dragging);
}
