//
// Created by fungp on 2024/5/17.
//

#ifndef BATTLEFIELD_HPP
#define BATTLEFIELD_HPP
#include "Enchant.hpp"
#include "BackgroundImage.hpp"

class Wave{
public:
    void AddEnemy(std::shared_ptr<Enemy> target);
private:
    std::vector<std::shared_ptr<Enemy>> m_EnemyList;
};

using EnemyFactory = std::function<std::shared_ptr<Enemy>()>;

class Battlefield{
public:
    Battlefield(int waves);
    void addEnemyFactory(const EnemyFactory& factory);
    std::shared_ptr<Enemy> RandomEnemy();
protected:
    std::vector<std::shared_ptr<Wave>> m_waves;
    std::vector<EnemyFactory> m_EnemyFactories;
    int m_total;
};

class sample : public Battlefield{
public:
    sample();
};
#endif // BATTLEFIELD_HPP
