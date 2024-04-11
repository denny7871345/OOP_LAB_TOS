#include "Enemy.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"
#include "GiraffeText.hpp"
#include "config.hpp"
Enemy::Enemy(Type::Element_type type, int life, int attack, int defence, int CD):m_type(type),m_life(life),m_attack(attack)
,m_defence(defence),m_CD(CD),AnimatedCharacter({
          "../assets/sprites/pet/Default/Happy/1/001.png",
          "../assets/sprites/pet/ShutDown/Nomal_1/结束动画表情2_000_125.png",
          "../assets/sprites/pet/ShutDown/Nomal_1/结束动画表情2_001_125.png",
          "../assets/sprites/pet/ShutDown/Nomal_1/结束动画表情2_002_125.png",
          "../assets/sprites/pet/ShutDown/Nomal_1/结束动画表情2_003_125.png",
          "../assets/sprites/pet/ShutDown/Nomal_1/结束动画表情2_004_125.png",
          "../assets/sprites/pet/ShutDown/Nomal_1/结束动画表情2_005_125.png",
          "../assets/sprites/pet/ShutDown/Nomal_1/结束动画表情2_006_125.png",
          "../assets/sprites/pet/ShutDown/Nomal_1/结束动画表情2_007_125.png",
          "../assets/sprites/pet/ShutDown/Nomal_1/结束动画表情2_008_125.png",
          "../assets/sprites/pet/ShutDown/Nomal_1/结束动画表情2_009_125.png",
          "../assets/sprites/pet/ShutDown/Nomal_1/结束动画表情2_010_125.png",
          "../assets/sprites/pet/ShutDown/Nomal_1/结束动画表情2_011_125.png"
      }){
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
    m_text = std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf",150);
    m_text->SetZIndex(GetZIndex()+1);
    m_text->Start();
    m_text->SetColor(Type::TypeColor(m_type));
    std::string token;
    token = std::to_string(m_life * 100 / m_firstLife) + "%(" + std::to_string(m_FirstCD) + ")";
    m_text->SetText(token);
}

void Enemy::DealtDamage(int Damage, bool Defence, DragingDatas datas) {
    int damage = Conflict(datas.m_Attackertype,Damage);
    if(damage ==0)
        return;

    bool effectedDamage = true;
    for(int i=0;i<m_SkillList.size();i++){
        effectedDamage = (effectedDamage && m_SkillList[i]->SkillsCheck(datas));
    }
    if(effectedDamage){
        if(Defence){
            if(damage > m_defence){
                LOG_DEBUG("Enemy has dealt {} damage left.",
                          damage -m_defence);
                m_life -= (damage -m_defence);
            }else{
                LOG_DEBUG("Enemy has dealt 1 damage left.");
                m_life -= 1;
            }
        }else{
            LOG_DEBUG("Enemy has dealt {} damage left.", damage);
            m_life -= damage;
        }
    }else{
        m_life -= 1;
    }
    m_hasBeenHit = true;
}

void Enemy::RoundUp() {
    m_hasBeenHit = false;
    std::string token;
    token = std::to_string(m_life * 100 / m_firstLife) + "%(" + std::to_string(m_CD) + ")";
    m_text->SetText(token);
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
    m_Transform.scale = {0.2,0.2};
    auto delta = static_cast<float>(Util::Time::GetDeltaTime());
    Util::Transform deltaTransform{
        dir * delta * 100.0F, 2 * delta,
        glm::vec2(0.5, 0.5) };
    pos += deltaTransform.translation;
    this->Draw();
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

int Enemy::Conflict(Type::Element_type type, int Damage) {
    float flag = 1;
    switch(m_type) {
        case Type::Element_type::Fire:
            if(type == Type::Element_type::Water){
                flag = 1.5;
            }else if(type == Type::Element_type::Grass){
                flag = 0.5;
            }
            break;
        case Type::Element_type::Water:
            if(type == Type::Element_type::Grass){
                flag = 1.5;
            }else if(type == Type::Element_type::Fire){
                flag = 0.5;
            }
            break;
        case Type::Element_type::Grass:
            if(type == Type::Element_type::Fire){
                flag = 1.5;
            }else if(type == Type::Element_type::Water){
                flag = 0.5;
            }
            break;
        case Type::Element_type::Light:
            if(type == Type::Element_type::Dark){
                flag = 1.5;
            }
            break;
        case Type::Element_type::Dark:
            if(type == Type::Element_type::Light){
                flag = 1.5;
            }
            break;
        default:
            break;
    }
    return flag * Damage;
}


