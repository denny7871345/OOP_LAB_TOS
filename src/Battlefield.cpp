//
// Created by fungp on 2024/5/17.
//

#include "Battlefield.hpp"
Battlefield::Battlefield() {

}
void Wave::AddEnemy(std::shared_ptr<Enemy> target) {
    m_EnemyList.push_back(target);
}

sample::sample() {
    auto Enemytoken1 = std::make_shared<Enemy>(Type::Element_type::Light,59537,4586,760,2);
    auto Enemytoken2 = std::make_shared<Enemy>(Type::Element_type::Light,59537,4586,760,2);
    Enemytoken1->SetPos(0,3);
    m_waves[0]->AddEnemy(Enemytoken1);
    Enemytoken2->SetPos(1,3);
    m_waves[0]->AddEnemy(Enemytoken2);
}