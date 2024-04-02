#include "BattleSystem.hpp"
#include "Enchant.hpp"
#include "Enemy.hpp"
void BattleSystem::Start() {
    ResetRound();
    m_DraggingTime = 5;
    auto Enemytoken = std::make_shared<Enemy>(Type::Element_type::Fire,20000,2300,10,2);
    /*auto ShieldToken1 = std::make_shared<FirstComboShield>(6);
    Enemytoken->AddSkill(ShieldToken1);*/
    auto Attacking = std::make_shared<StrongerSilver>();
    Enemytoken->SetAttackingMethod(Attacking);
    m_enemy.push_back(Enemytoken);
    std::shared_ptr<Mori> token = std::make_shared<Mori>(m_Enchant);
    m_team.push_back(token);
    std::shared_ptr<Sean> token2 = std::make_shared<Sean>(m_Enchant);
    m_team.push_back(token2);
    std::shared_ptr<WaterSlime> token3 = std::make_shared<WaterSlime>(m_Enchant);
    m_team.push_back(token3);
    std::shared_ptr<WaterBeast> token4 = std::make_shared<WaterBeast>(m_Enchant);
    m_team.push_back(token4);
    for(int i=0;i<m_team.size();i++){
        m_MaxLife += m_team[i]->GetLife();
        m_team[i]->SetEnemy(m_enemy);
    }
    m_life = m_MaxLife;
    m_audioSystem.Start();
}

void BattleSystem::SkillTrigger(int index) {
    m_team[index]->Skill();
}

void BattleSystem::SetCombo(int combo) {
    m_combo = combo;
}

void BattleSystem::AddCombo(int combo) {
    bool flag = false;
    if(m_combo == 0 ){
        flag = true;
    }
    m_combo += combo;
    if(flag){
        m_ComboAddition += m_addCombo * (combo-1);
    }else{
        m_ComboAddition += m_addCombo * combo;
    }
}
void BattleSystem::AddExCombo(int combo) {
    m_exCombo += combo;
}

void BattleSystem::ResetRound() {
    m_ComboAddition = 0;
    m_addCombo = 0.25;
    m_firstCombo = 0;
    m_combo = 0;
    m_exCombo = 0;
    m_firstErase = {0,0,0,0,0,0};
    m_totalErase = {0,0,0,0,0,0};
    m_StoneDamage = {0,0,0,0,0,0};
    m_powerUpBeenErase = {false,false,false,false,false,false};
}
bool BattleSystem::DealPair(std::vector<std::shared_ptr<Stone>> Lists) {
    if(Lists[0]->IfAnimationEnds()){
        AddCombo(1);
        m_StoneDamage[Type::FindIndex(Lists[0]->GetType())] += 0.5 + (0.25 * (Lists.size()-1));
        m_totalErase[Type::FindIndex(Lists[0]->GetType())] += Lists.size();
        return true;
    }
    for(int i=0;i<Lists.size();i++){
        if(! Lists[i]->IsPlaying()){
            if(Lists[i]->IsPowerUp()){
                m_StoneDamage[Type::FindIndex(Lists[0]->GetType())] += 0.3;
                m_powerUpBeenErase[Type::FindIndex(Lists[i]->GetType())] = true;
            }
            Lists[i]->SetPlaying(true);
            if(i==0){
                if(Lists.size() >= 5){
                    m_Enchant->MustFall(Lists[0]->GetType(), true);
                    static auto SFX = Util::SFX("../assets/audio/Combo/eat5Gem.wav");
                    SFX.Play();
                }else{
                    AddCombo(1);
                }
                m_StoneDamage[Type::FindIndex(Lists[0]->GetType())] += 0.5 + (0.25 * (Lists.size()-1));
                m_totalErase[Type::FindIndex(Lists[0]->GetType())] += Lists.size();
                m_audioSystem.PlayComboSound(m_combo);
            }
        }
    }
    return false;
}
bool BattleSystem::DealFirstPiar(std::vector<std::shared_ptr<Stone>> Lists) {
    if(Lists[0]->IfAnimationEnds()){
        return true;
    }
    for(int i=0;i<Lists.size();i++){
        if(! Lists[i]->IsPlaying()){
            if(Lists[i]->IsPowerUp()){
                m_StoneDamage[Type::FindIndex(Lists[0]->GetType())] += 0.3;
                m_powerUpBeenErase[Type::FindIndex(Lists[i]->GetType())] = true;
            }
            Lists[i]->SetPlaying(true);
            if(i==0){
                if(Lists.size() >= 5){
                    m_Enchant->MustFall(Lists[0]->GetType(), true);
                    static auto SFX = Util::SFX("../assets/audio/Combo/eat5Gem.wav");
                    SFX.Play();
                }else{
                    AddCombo(1);
                    m_audioSystem.PlayComboSound(m_combo);
                }
                m_StoneDamage[Type::FindIndex(Lists[0]->GetType())] += 0.5 + (0.25 * (Lists.size()-1));
                m_totalErase[Type::FindIndex(Lists[0]->GetType())] += Lists.size();
                m_firstCombo +=1 ;
                m_firstErase[Type::FindIndex(Lists[0]->GetType())] += Lists.size();
            }
        }
    }
    return false;
}

void BattleSystem::ShowData() {
    LOG_DEBUG("first erase:[{},{},{},{},{},{}]",m_firstErase[0],m_firstErase[1],m_firstErase[2],m_firstErase[3],m_firstErase[4],m_firstErase[5]);
    LOG_DEBUG("total erase:[{},{},{},{},{},{}]",m_totalErase[0],m_totalErase[1],m_totalErase[2],m_totalErase[3],m_totalErase[4],m_totalErase[5]);
    LOG_DEBUG("total StoneDamage:[{}%,{}%,{}%,{}%,{}%,{}%]",m_StoneDamage[0]*100,m_StoneDamage[1]*100,m_StoneDamage[2]*100,m_StoneDamage[3]*100,m_StoneDamage[4]*100,m_StoneDamage[5]*100);
    LOG_DEBUG("PowerUP Erase:[{},{},{},{},{},{}]",m_powerUpBeenErase[0],m_powerUpBeenErase[1],m_powerUpBeenErase[2],m_powerUpBeenErase[3],m_powerUpBeenErase[4],m_powerUpBeenErase[5]);
    LOG_DEBUG("first combo:{}",m_firstCombo);
    LOG_DEBUG("Total combo:{}",m_combo);
    LOG_DEBUG("Combo Addition:{}%",m_ComboAddition * 100);
    DamageSettle();
}

void BattleSystem::SetEnchant(std::shared_ptr<Enchant> target) {
    m_Enchant = target;
}

void BattleSystem::DamageSettle() {
    int totalHeal=0;
    DragingDatas token = GetDragDatas();
    for(int i=0;i < m_team.size() ;i++){
        totalHeal += m_team[i]->GetHeal() * m_StoneDamage[5] ;
        int Damage = m_team[i]->GetAtk() * m_ComboAddition * m_StoneDamage[Type::FindIndex(m_team[i]->GetType())];
        LOG_DEBUG("Member{} deals {} damage",i,Damage);
        token.m_Attackertype = m_team[i]->GetType();
        m_team[i]->Strike(false,Damage,true,token);
    }
    if(m_life + totalHeal * m_ComboAddition > m_MaxLife){
        m_life = m_MaxLife;
        LOG_DEBUG("you are full of Life");
    }else{
        m_life += totalHeal * m_ComboAddition ;
        LOG_DEBUG("U heal {} life.",totalHeal);
    }
    //Enemy's turn
    for(int i=0; i < m_enemy.size();i++){
        LOG_DEBUG("Enemy{}'s Turn!!!",i);
        m_enemy[i]->AddCD(-1);
        if(m_enemy[i]->GetCD() == 0){
            LOG_DEBUG("Enemy Attack!!!");

            auto damage = m_enemy[i]->Attack(token);

            for(int j=0;j<damage.size();j++){
                LOG_DEBUG("U are dealt {} damages.",damage[j]);
                m_life -= damage[j];
                LOG_DEBUG("U have {} life left.",m_life);
            }

            m_enemy[i]->AddCD(2);
        }
        m_enemy[i]->RoundUp();
        LOG_DEBUG("Enemy has {} life left. And CD = {}",m_enemy[i]->GetLife(),m_enemy[i]->GetCD());
    }


}

float BattleSystem::GetDraggingTime() {
    return m_DraggingTime;
}

DragingDatas BattleSystem::GetDragDatas() {
    DragingDatas token;
    token.m_totalErase = m_totalErase;
    token.m_firstCombo = m_firstCombo;
    token.m_powerUpBeenErase = m_powerUpBeenErase;
    token.m_combo = m_combo;
    token.m_exCombo = m_exCombo;
    return token;
}