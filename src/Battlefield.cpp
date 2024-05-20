//
// Created by fungp on 2024/5/17.
//

#include "Battlefield.hpp"
#include <random>

int Wave::Size() {
    return m_EnemyList.size();
}

std::shared_ptr<Enemy> Wave::GetEnemy(int num) {
    return m_EnemyList[num];
}


Battlefield::Battlefield(int waves):m_total(waves) {
    for(int i=0;i<waves;i++){
        m_waves.push_back(std::make_shared<Wave>());
    }
}

int Battlefield::Size() {
    return m_total;
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
    std::shared_ptr<Enemy> Enemy1 = std::make_shared<Enemy>(Type::Element_type::Fire,220000,6653,99,3);
    auto sheildToken = std::make_shared<ComboShield>(7);
    Enemy1->AddSkill(sheildToken);
    std::shared_ptr<Enemy> Enemy2 = std::make_shared<Enemy>(Type::Element_type::Grass,420000,4884,100,2);
    auto AttackingToken = std::make_shared<KeepFight>();
    Enemy2->SetAttackingMethod(AttackingToken);
    Enemy1->SetPos(0,2);
    Enemy2->SetPos(1,2);

    std::vector<std::string> list = {"../assets/sprites/Characters/166n.png",
                                     "../assets/sprites/Characters/1.png",
                                     "../assets/sprites/Characters/2.png",
                                     "../assets/sprites/Characters/3.png"};
    auto token  = std::make_shared<Util::Animation>(list, false, 200, false, 0);
    token->Pause();
    Enemy1->SetScale(0.8);
    Enemy1->SetYpos(250);
    Enemy1->SetAnimation(token);
                            list = {"../assets/sprites/Characters/169n.png",
                                     "../assets/sprites/Characters/1.png",
                                     "../assets/sprites/Characters/2.png",
                                     "../assets/sprites/Characters/3.png"};
    token  = std::make_shared<Util::Animation>(list, false, 200, false, 0);
    token->Pause();
    Enemy2->SetScale(0.8);
    Enemy2->SetAnimation(token);
    Enemy2->SetYpos(250);
    m_waves[5]->AddEnemy(Enemy1);
    m_waves[5]->AddEnemy(Enemy2);

    //Setting Boss
    auto Boss = std::make_shared<Enemy>(Type::Element_type::Water,850000,1,202,1);
    auto AttackingToken1 = std::make_shared<PercentageAttacking>(0.5);
    Boss->SetAttackingMethod(AttackingToken1);
    Boss->SetPos(0,1);

    list = {"../assets/sprites/Characters/118n.png",
            "../assets/sprites/Characters/1.png",
            "../assets/sprites/Characters/2.png",
            "../assets/sprites/Characters/3.png"};

    token  = std::make_shared<Util::Animation>(list, false, 200, false, 0);
    token->Pause();
    Boss->SetScale(0.8);
    Boss->SetYpos(250);
    Boss->SetAnimation(token);



    m_waves[6]->AddEnemy(Boss);

}

std::shared_ptr<Wave> Battlefield::GetWave(int num) {
    return m_waves[num];
}