#ifndef BATTLESYSTEM_HPP
#define BATTLESYSTEM_HPP

#include "Stone.hpp"
#include "Member.hpp"
#include "AudioSystem.hpp"

class Enchant;

class BattleSystem {
public:
    void Update();
    void SetEnchant(std::shared_ptr<Enchant> target);
    float GetDraggingTime();
    void AddDraggingTime();
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
private:
    DragingDatas GetDragDatas();
    std::vector<std::shared_ptr<Enemy>> m_enemy;
    AudioSystem m_audioSystem;
    std::vector<float> m_StoneDamage={0,0,0,0,0,0};
    std::vector<int> m_totalErase={0,0,0,0,0,0};
    std::vector<int> m_firstErase={0,0,0,0,0,0};
    std::vector<bool>m_powerUpBeenErase={false,false,false,false,false,false};
    std::shared_ptr<Enchant> m_Enchant;
    std::vector<std::shared_ptr<Member>> m_team;
    int m_life;
    int m_MaxLife;
    int m_combo;
    int m_exCombo;
    int m_firstCombo;
    float m_addCombo;
    float m_ComboAddition;
    float m_DraggingTime;
};

#endif
