#ifndef BATTLESYSTEM_HPP
#define BATTLESYSTEM_HPP

#include "iostream"
#include "Stone.hpp"
#include "Member.hpp"
#include "AudioSystem.hpp"
#include "AbilityStatus.hpp"

class Enchant;

class BattleSystem {
public:
    typedef void (BattleSystem::*FuncPtr)(int);
    MemberSettingData CreateMemberData();
    void Update();
    void CheatCodeOfKill();
    void SetEnchant(std::shared_ptr<Enchant> target);
    float GetDraggingTime();
    void AddDraggingTime();
    void StateTrigger(AbilityType state);
    void Start();
    void ShowData();
    void ResetRound();
    bool DealPair(std::vector<std::shared_ptr<Stone>> Lists);
    bool DealFirstPiar(std::vector<std::shared_ptr<Stone>> Lists);
    void AddCombo(int combo);
    void SkillTrigger(int index);
    void AddExCombo(int combo);
    void SetCombo(int combo);
    void DamageSettle();
    void AddStatus(std::shared_ptr<AbilityStatus> target);
    void AddStatusToEnemy(std::shared_ptr<AbilityStatus> target);
    void SetComboDisplay(bool visible);
    void NormalTeamGetDamage(int Damage);
    void SpecialTeamGetDamage(int Damage);
    FuncPtr GetDamage = &BattleSystem::NormalTeamGetDamage;
private:

    DragingDatas GetDragDatas();
    std::vector<std::shared_ptr<Enemy>> m_enemy;
    AudioSystem m_audioSystem;
    std::shared_ptr<std::vector<std::shared_ptr<AbilityStatus>>> m_status;
    std::shared_ptr<std::vector<float>> m_ElementAddition;
    std::shared_ptr<std::vector<float>> m_FirstElementAddition;
    std::shared_ptr<std::vector<float>> m_RaceAddition;
    std::shared_ptr<std::vector<float>> m_FirstRaceAddition;
    std::shared_ptr<float> m_dealtDamageDecrease = std::make_shared<float>(0.0f);
    std::vector<float> m_StoneDamage={0,0,0,0,0,0};
    std::shared_ptr<std::vector<int>> m_totalErase;
    std::shared_ptr<std::vector<int>> m_firstErase;
    std::vector<bool>m_powerUpBeenErase={false,false,false,false,false,false};
    std::shared_ptr<Enchant> m_Enchant;
    std::shared_ptr<GiraffeText> m_LifeDisplay = std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf",15);
    std::shared_ptr<GiraffeText> m_ComboDisplay = std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf",120);
    std::shared_ptr<GiraffeText> m_ComboAdditionDisplay = std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf",30);
    std::vector<std::shared_ptr<Member>> m_team;
    std::vector<std::shared_ptr<LeaderSkill>> m_LeaderSkill;
    std::shared_ptr<int> m_life = std::make_shared<int>(0);
    std::shared_ptr<int> m_MaxLife= std::make_shared<int>(0);
    int m_combo;
    int m_exCombo;
    int m_firstCombo;
    std::shared_ptr<float> m_addCombo = std::make_shared<float>(0.25);
    float m_ComboAddition;
    float m_DraggingTime;

};

#endif
