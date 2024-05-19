//
// Created by fungp on 2024/5/17.
//

#include "Battlefield.hpp"
Battlefield::Battlefield(int waves):m_total(waves) {
}

void Battlefield::addEnemyFactory(const EnemyFactory &factory) {
    m_EnemyFactories.push_back(factory);
}

std::shared_ptr<Enemy> Battlefield::RandomEnemy() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, m_EnemyFactories.size() - 1);
    int randomIndex = dis(gen);
    return m_EnemyFactories[randomIndex]();
}

void Wave::AddEnemy(std::shared_ptr<Enemy> target) {
    m_EnemyList.push_back(target);
}

//https://www.tosapp.tw/task-c-43.html
sample::sample(): Battlefield(7) {

    //Setting the monster may appear in this Battlefield
    this->addEnemyFactory([]() { return std::make_shared<EnemyLightGirl>(); });
    this->addEnemyFactory([]() { return std::make_shared<EnemyLightWerewolf>(); });
    this->addEnemyFactory([]() { return std::make_shared<EnemyLightSlime>(); });
    this->addEnemyFactory([]() { return std::make_shared<EnemyLightElf>(); });


    //setting Random Enemy
    for (int i = 0; i < 5; ++i) {
        for(int j=0;j<3;j++){
            std::shared_ptr<Enemy> enemy = RandomEnemy();
            enemy->SetPos(j,3);
            m_waves[i]->AddEnemy(enemy);
        }
    }
    //Setting the specific Enemy
    auto Enemy1 = std::make_shared<Enemy>(Type::Element_type::Fire,220000,6653,99,3);
    auto sheildToken = std::make_shared<ComboShield>(7);
    Enemy1->AddSkill(sheildToken);
    auto Enemy2 = std::make_shared<Enemy>(Type::Element_type::Grass,420000,4884,100,2);
    auto AttackingToken = std::make_shared<KeepFight>();
    Enemy2->SetAttackingMethod(AttackingToken);
    m_waves[6]->AddEnemy(Enemy1);
    m_waves[6]->AddEnemy(Enemy2);

    //Setting Boss

    auto Boss = std::make_shared<Enemy>(Type::Element_type::Water,850000,1,202,1);
    auto AttackingToken1 = std::make_shared<PercentageAttacking>(0.5);
    Boss->SetAttackingMethod(AttackingToken1);
    m_waves[7]->AddEnemy(Boss);
}