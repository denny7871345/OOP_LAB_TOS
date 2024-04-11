#include "Enemy.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"
#include "GiraffeText.hpp"
#include "config.hpp"
Enemy::Enemy(Type::Element_type type, int life, int attack, int defence, int CD):m_type(type),m_life(life),m_attack(attack)
,m_defence(defence),m_CD(CD),AnimatedCharacter({"../assets/sprites/cat/cat-0.bmp",
                         "../assets/sprites/cat/cat-1.bmp"
                         ,"../assets/sprites/cat/cat-2.bmp"
                         ,"../assets/sprites/cat/cat-3.bmp"
                         ,"../assets/sprites/cat/cat-4.bmp"
                         ,"../assets/sprites/cat/cat-5.bmp"
                         ,"../assets/sprites/cat/cat-6.bmp"
                         ,"../assets/sprites/cat/cat-7.bmp"}){
    SetZIndex(5);
    m_Animation->SetLooping(true);
    m_Animation->SetInterval(100);
    m_Animation->Pause();
    m_firstLife = m_life;
    m_FirstAttack = m_attack;
    m_FirstCD = m_CD;
    m_FirstDefence = m_defence;
    m_firstType = m_type;
    m_FirstCD = m_CD;
    m_text = std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf",200);
    m_text->SetZIndex(GetZIndex()+1);
    m_text->Start();
    m_text->SetColor(Type::TypeColor(m_type));
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

void Enemy::Update() {
    static glm::vec2 dir = {0, 0};
    auto &pos = m_Transform.translation;
    auto x_pos = WINDOW_WIDTH / (m_pos.y) ;
    m_Transform.translation = { -225 + x_pos * (0.5 + m_pos.x) ,200};
    m_Transform.scale = { 1.0 / m_pos.y, 1.0 / m_pos.y};
    auto delta = static_cast<float>(Util::Time::GetDeltaTime());
    Util::Transform deltaTransform{
        dir * delta * 100.0F, 2 * delta,
        glm::vec2(0.5, 0.5) };
    pos += deltaTransform.translation;
    this->Draw();
    std::string token;
    token = std::to_string(m_life * 100 / m_firstLife) + "%";
    m_text->SetText(token);
    m_text->Update(m_Transform);
}

void Enemy::SetPos(int x, int y) {
    m_pos = {x,y};
}

void Enemy::SetDef(float value) {
    m_defence = m_FirstDefence * value;
}

void Enemy::SetAtk(float value) {
    m_attack = m_FirstAttack * value;
}

void Enemy::DefReset() {
    m_defence = m_FirstDefence;
}

void Enemy::AtkReset() {
    m_attack = m_FirstAttack;
}

void Enemy::AddStatus(const std::shared_ptr<AbilityStatus>& target) {
    m_status.push_back(target);
}