#include "BattleSystem.hpp"
#include "Enchant.hpp"
#include "Enemy.hpp"
void BattleSystem::Start() {
    std::vector<float> vec = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    m_FirstElementAddition = std::make_shared<std::vector<float>>(vec);
    m_ElementAddition = std::make_shared<std::vector<float>>(vec);
    std::vector<float> vec2 = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
    m_FirstRaceAddition = std::make_shared<std::vector<float>>(vec2);
    m_RaceAddition = std::make_shared<std::vector<float>>(vec2);
    std::vector<int> vec3 = {0,0,0,0,0,0};
    m_totalErase = std::make_shared<std::vector<int>>(vec3);
    m_firstErase = std::make_shared<std::vector<int>>(vec3);
    m_DraggingTime = 5;
    m_status =  std::make_shared<std::vector<std::shared_ptr<AbilityStatus>>>();
    //Enemy Setting
    auto Enemytoken = std::make_shared<Enemy>(Type::Element_type::Light,1000000,99999,100000,1);
    Enemytoken->SetPos(0,1);
    /*auto Enemytoken2 = std::make_shared<Enemy>(Type::Element_type::Grass,100000,2300,10,2);
    Enemytoken2->SetPos(1,3);
    auto Enemytoken3 = std::make_shared<Enemy>(Type::Element_type::Water,200000,2300,10,2);
    Enemytoken3->SetPos(2,3);*/
    /*auto ShieldToken1 = std::make_shared<FirstComboShield>(6);
    Enemytoken->AddSkill(ShieldToken1);*/
    /*auto Attacking = std::make_shared<DoubleStrike>();
    Enemytoken->SetAttackingMethod(Attacking); */
    m_enemy.push_back(Enemytoken);
    /*m_enemy.push_back(Enemytoken2);
    m_enemy.push_back(Enemytoken3);*/

    //member Setting
    auto Membertoken = CreateMemberData();
    std::shared_ptr<WaterRanger> token1 = std::make_shared<WaterRanger>(Membertoken);
    m_team.push_back(token1);
    std::shared_ptr<Eduard> token2 = std::make_shared<Eduard>(Membertoken);
    m_team.push_back(token2);
    std::shared_ptr<LightBeast> token3 = std::make_shared<LightBeast>(Membertoken);
    m_team.push_back(token3);
    std::shared_ptr<GrassSlime> token4 = std::make_shared<GrassSlime>(Membertoken);
    m_team.push_back(token4);
    std::shared_ptr<WaterRanger> token5 = std::make_shared<WaterRanger>(Membertoken);
    m_team.push_back(token5);
    std::shared_ptr<Athana> token6 = std::make_shared<Athana>(Membertoken);
    m_team.push_back(token6);

    // Leader Skill Setting
    auto LeaderToken = m_team[0]->GetLeaderSkill();
    for(int i=0;i<LeaderToken.size();i++) m_LeaderSkill.push_back(LeaderToken[i]);
    LeaderToken = m_team[5]->GetLeaderSkill();
    for(int i=0;i<LeaderToken.size();i++) m_LeaderSkill.push_back(LeaderToken[i]);

    for(int i=0;i < m_team.size();i++){
        (*m_MaxLife) += m_team[i]->GetLife();
        m_team[i]->SetEnemy(m_enemy);
    }
    (*m_life) = (*m_MaxLife);
    m_audioSystem.Start();

    StateTrigger(AbilityType::Setting);

    ResetRound();
    std::string lifeToken = std::to_string((*m_life)) + "/"  +std::to_string(*m_MaxLife);
    m_LifeDisplay->Start();
    m_LifeDisplay->SetColor(Util::Colors::PINK);
    m_LifeDisplay->SetZIndex(5);
    m_LifeDisplay->SetText(lifeToken);
    m_ComboDisplay->Start();
    m_ComboDisplay->SetColor(Util::Colors::WHITE);
    m_ComboDisplay->SetZIndex(5);
    m_ComboDisplay->SetText("Ambatukam");
    m_ComboAdditionDisplay->Start();
    m_ComboAdditionDisplay->SetColor(Util::Colors::WHITE);
    m_ComboAdditionDisplay->SetZIndex(5);
    m_ComboAdditionDisplay->SetText("Ambatukam");
    SetComboDisplay(false);
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
        m_ComboAddition += *(m_addCombo) * (combo-1);
    }else{
        m_ComboAddition += *(m_addCombo) * combo;
    }
}
void BattleSystem::AddExCombo(int combo) {
    m_exCombo += combo;
}

void BattleSystem::ResetRound() {
    m_ComboAddition = 1;
    m_firstCombo = 0;
    m_combo = 0;
    m_exCombo = 0;
    m_RaceAddition = m_FirstRaceAddition;
    for(int i=0;i<6;i++){
        (*m_totalErase)[i] = 0;
        (*m_firstErase)[i] = 0;
        if(i<5)(*m_ElementAddition)[i] = (*m_FirstElementAddition)[i];
        (*m_RaceAddition)[i] = (*m_FirstRaceAddition)[i];
    }
    m_StoneDamage = {0,0,0,0,0,0};
    m_powerUpBeenErase = {false,false,false,false,false,false};

    for(int i=0;i<m_status->size();i++){
        if((*m_status)[i]->RoundUp()){
            (*m_status)[i]->Reset();
            (*m_status).erase((*m_status).begin()+i);
        }
    }
    for(int i=0;i<m_LeaderSkill.size();i++){
        m_LeaderSkill[i]->SkillReset();
    }

}
bool BattleSystem::DealPair(std::vector<std::shared_ptr<Stone>> Lists) {
    if(Lists[0]->IfAnimationEnds()){
        m_StoneDamage[Type::FindIndex(Lists[0]->GetType())] += 0.5 + (0.25 * (Lists.size()-1));
        (*m_totalErase)[Type::FindIndex(Lists[0]->GetType())] += Lists.size();
        LOG_DEBUG("total erase:[{},{},{},{},{},{}]",(*m_totalErase)[0],(*m_totalErase)[1],(*m_totalErase)[2],(*m_totalErase)[3],(*m_totalErase)[4],(*m_totalErase)[5]);
        StateTrigger(AbilityType::EraseOfStone);
        return true;
    }
    for(int i=0;i<Lists.size();i++){
        if(! Lists[i]->IsPlaying()){
            SetComboDisplay(true);
            if(Lists[i]->IsPowerUp()){
                m_StoneDamage[Type::FindIndex(Lists[0]->GetType())] += 0.3;
                m_powerUpBeenErase[Type::FindIndex(Lists[i]->GetType())] = true;
            }
            Lists[i]->SetPlaying(true);
            if(i==0){
                if(Lists.size() >= 5){
                    AddCombo(1);
                    m_Enchant->MustFall(Lists[0]->GetType(), 1,true);
                    static auto SFX = Util::SFX("../assets/audio/Combo/eat5Gem.wav");
                    SFX.Play();
                }else{
                    AddCombo(1);
                }
                m_StoneDamage[Type::FindIndex(Lists[0]->GetType())] += 0.5 + (0.25 * (Lists.size()-1));
                m_audioSystem.PlayComboSound(m_combo);
            }
        }
    }
    return false;
}
bool BattleSystem::DealFirstPiar(std::vector<std::shared_ptr<Stone>> Lists) {
    if(Lists[0]->IfAnimationEnds()){
        LOG_DEBUG("total erase:[{},{},{},{},{},{}]",(*m_totalErase)[0],(*m_totalErase)[1],(*m_totalErase)[2],(*m_totalErase)[3],(*m_totalErase)[4],(*m_totalErase)[5]);
        StateTrigger(AbilityType::EraseOfStone);
        return true;
    }
    for(int i=0;i<Lists.size();i++){
        if(! Lists[i]->IsPlaying()){
            SetComboDisplay(true);
            if(Lists[i]->IsPowerUp()){
                m_StoneDamage[Type::FindIndex(Lists[0]->GetType())] += 0.3;
                m_powerUpBeenErase[Type::FindIndex(Lists[i]->GetType())] = true;
            }
            Lists[i]->SetPlaying(true);
            if(i==0){
                if(Lists.size() >= 5){
                    AddCombo(1);
                    m_Enchant->MustFall(Lists[0]->GetType(), 1,true);
                    static auto SFX = Util::SFX("../assets/audio/Combo/eat5Gem.wav");
                    SFX.Play();
                }else{
                    AddCombo(1);
                    m_audioSystem.PlayComboSound(m_combo);
                }
                m_StoneDamage[Type::FindIndex(Lists[0]->GetType())] += 0.5 + (0.25 * (Lists.size()-1));
                (*m_totalErase)[Type::FindIndex(Lists[0]->GetType())] += Lists.size();
                m_firstCombo +=1 ;
                (*m_firstErase)[Type::FindIndex(Lists[0]->GetType())] += Lists.size();
            }
        }
    }
    return false;
}

void BattleSystem::ShowData() {
    LOG_DEBUG("U have {} AblityStatus",(*m_status).size());
    LOG_DEBUG("first erase:[{},{},{},{},{},{}]",(*m_firstErase)[0],(*m_firstErase)[1],(*m_firstErase)[2],(*m_firstErase)[3],(*m_firstErase)[4],(*m_firstErase)[5]);
    LOG_DEBUG("total erase:[{},{},{},{},{},{}]",(*m_totalErase)[0],(*m_totalErase)[1],(*m_totalErase)[2],(*m_totalErase)[3],(*m_totalErase)[4],(*m_totalErase)[5]);
    LOG_DEBUG("total StoneDamage:[{}%,{}%,{}%,{}%,{}%,{}%]",m_StoneDamage[0]*100,m_StoneDamage[1]*100,m_StoneDamage[2]*100,m_StoneDamage[3]*100,m_StoneDamage[4]*100,m_StoneDamage[5]*100);
    LOG_DEBUG("PowerUP Erase:[{},{},{},{},{},{}]",m_powerUpBeenErase[0],m_powerUpBeenErase[1],m_powerUpBeenErase[2],m_powerUpBeenErase[3],m_powerUpBeenErase[4],m_powerUpBeenErase[5]);
    LOG_DEBUG("first combo:{}",m_firstCombo);
    LOG_DEBUG("Total combo:{}",m_combo);
    LOG_DEBUG("Combo Addition:{}%",m_ComboAddition * 100);
    std::vector<float> &vecRef = *m_ElementAddition;
    LOG_DEBUG("Leader Element Addition:[{},{},{},{},{}]", vecRef[0],vecRef[1],vecRef[2],vecRef[3],vecRef[4] );
    std::vector<float> &vecRef2 = *m_RaceAddition;
    LOG_DEBUG("Leader Race Addition:[{},{},{},{},{},{}]", vecRef2[0],vecRef2[1],vecRef2[2],vecRef2[3],vecRef2[4],vecRef2[5] );
}

void BattleSystem::SetEnchant(std::shared_ptr<Enchant> target) {
    m_Enchant = target;
}

void BattleSystem::DamageSettle() {
    ShowData();
    int totalHeal=0;
    StateTrigger(AbilityType::DamageSettle);
    DragingDatas token = GetDragDatas();
    for(int i=0;i < m_team.size() ;i++){
        totalHeal += m_team[i]->GetHeal() * m_StoneDamage[5] ;
        std::vector<float> &ElementAddition = *m_ElementAddition;
        std::vector<float> &RaceAddition = *m_RaceAddition;
        //LOG_DEBUG("[{},{},{},{},{},{}]",RaceAddition[0],RaceAddition[1],RaceAddition[2],RaceAddition[3],RaceAddition[4],RaceAddition[5]);
        //LOG_DEBUG("this member's Race Index is:{}", Type::FindIndex(m_team[i]->GetRace()) );
        int Damage = m_team[i]->GetAtk() * m_ComboAddition * m_StoneDamage[Type::FindIndex(m_team[i]->GetType())] *
                     ElementAddition[Type::FindIndex(m_team[i]->GetType())] * RaceAddition[Type::FindIndex(m_team[i]->GetRace())];
        LOG_DEBUG("Member{} deals ({}*{}*{}(E)*{}(R)*{})={} damage",i+1,m_team[i]->GetAtk(),m_StoneDamage[Type::FindIndex(m_team[i]->GetType())],ElementAddition[Type::FindIndex(m_team[i]->GetType())],RaceAddition[Type::FindIndex(m_team[i]->GetRace())],m_ComboAddition,Damage);
        token.m_Attackertype = m_team[i]->GetType();
        m_team[i]->Strike(true,Damage,true,token);
    }
    if((*m_life) + totalHeal * m_ComboAddition > (*m_MaxLife)){
        (*m_life) = (*m_MaxLife);
        //LOG_DEBUG("you are full of Life");
    }else{
        (*m_life) += totalHeal * m_ComboAddition ;
        //LOG_DEBUG("U heal {} life.",totalHeal);
    }
    //Enemy's turn
    for(int i=0; i < m_enemy.size();i++){

        if(m_enemy[i]->GetLife() <= 0){
            m_enemy[i]->SetPlaying(true);
            continue;
        }
        m_enemy[i]->AddCD(-1);
        if(m_enemy[i]->GetCD() == 0){
            //LOG_DEBUG("Enemy Attack!!!");

            auto damage = m_enemy[i]->Attack(token);

            for(int j=0;j<damage.size();j++){
                //LOG_DEBUG("U are dealt {} damages.",damage[j]);
                (this->*GetDamage)(damage[j]);
                //LOG_DEBUG("U have {} life left.",(*m_life));
            }
            m_enemy[i]->AddCD(2);
        }
        m_enemy[i]->RoundUp();
        //LOG_DEBUG("Enemy has {} life left. And CD = {}",m_enemy[i]->GetLife(),m_enemy[i]->GetCD());
    }
    std::string lifeToken = std::to_string((*m_life)) + "/"  +std::to_string(*m_MaxLife);
    m_LifeDisplay->SetText(lifeToken);

}

float BattleSystem::GetDraggingTime() {
    return m_DraggingTime;
}

DragingDatas BattleSystem::GetDragDatas() {
    DragingDatas token;
    token.m_totalErase = m_totalErase;
    token.m_firstErase = m_firstErase;
    token.m_firstCombo = m_firstCombo;
    token.m_powerUpBeenErase = m_powerUpBeenErase;
    token.m_combo = m_combo;
    token.m_exCombo = m_exCombo;
    return token;
}

void BattleSystem::Update() {
    for(int i=0;i<m_enemy.size();i++){
        if(m_enemy[i] != nullptr){
            m_enemy[i]->Update();
            if(m_enemy[i]->IfAnimationEnds()) m_enemy.erase(m_enemy.begin() + i);
        }
    }
    glm::vec2 lifePosition = {135,45};
    m_LifeDisplay->Update(lifePosition);
    lifePosition = {135,-250};
    m_ComboDisplay->SetText(std::to_string(m_combo));
    m_ComboDisplay->Update(lifePosition);
    lifePosition = {180,-310};
    m_ComboAdditionDisplay->SetText("+"+ std::to_string(int(m_ComboAddition*100)-100)+"%");
    m_ComboAdditionDisplay->Update(lifePosition);
}

void BattleSystem::AddStatus(std::shared_ptr<AbilityStatus> target) {
    (*m_status).push_back(target);
}

void BattleSystem::AddStatusToEnemy(std::shared_ptr<AbilityStatus> target) {
    for(int i=0;i<m_enemy.size();i++){
        m_enemy[i]->AddStatus(target);
    }
}

MemberSettingData BattleSystem::CreateMemberData() {
    MemberSettingData token;
    token.m_status = m_status;
    token.m_Enchant = m_Enchant;
    token.m_dealtDamageDecrease = m_dealtDamageDecrease;
    token.m_FirstAddition = m_FirstElementAddition;
    token.m_FirstRaceAddition = m_FirstRaceAddition;
    token.m_ElementAddition = m_ElementAddition;
    token.m_RaceAddition = m_RaceAddition;
    token.m_addCombo = m_addCombo;
    token.m_firstErase = m_firstErase;
    token.m_totalErase = m_totalErase;
    token.GetDamage = GetDamage;
    return token;
}

void BattleSystem::SetComboDisplay(bool visible) {
    m_ComboDisplay->SetVisible(visible);
    m_ComboAdditionDisplay->SetVisible(visible);
}

void BattleSystem::StateTrigger(AbilityType state) {
    for(int i=0;i<m_LeaderSkill.size();i++){
        if(m_LeaderSkill[i]->GetType() == state){
            m_LeaderSkill[i]->Skill();
        }
    }
    for(int i=0;i<m_status->size();i++){
        if((*m_status)[i]->GetType() == state){
            (*m_status)[i]->Trigger();
        }
    }
}

void BattleSystem::NormalTeamGetDamage(int Damage) {
    (*m_life) -= Damage * (1-(*m_dealtDamageDecrease));
}

void BattleSystem::SpecialTeamGetDamage(int Damage) {
    bool flag = false;
    flag = ((*m_life) >= (*m_MaxLife) * 0.5);
    (*m_life) -= Damage * (1-(*m_dealtDamageDecrease));
    if(flag && (*m_life<=0)) (*m_life) = 1;
}