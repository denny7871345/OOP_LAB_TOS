//
// Created by fungp on 2024/5/17.
//

#ifndef BATTLEFIELD_HPP
#define BATTLEFIELD_HPP
#include "iostream"
#include "memory"
#include "vector"
#include <functional>
#include "Enemy.hpp"

using EnemyFactory = std::function<std::shared_ptr<Enemy>()>;

class Wave{
public:
    void AddEnemy(std::shared_ptr<Enemy> target);
    std::shared_ptr<Enemy> GetEnemy(int num);
    int Size();
private:
    std::vector<std::shared_ptr<Enemy>> m_EnemyList;
};

class Battlefield{
public:
    Battlefield(int waves);
    std::shared_ptr<Wave> GetWave(int num);
    void addEnemyFactory(const EnemyFactory& factory);
    std::shared_ptr<Enemy> RandomEnemy();
    int Size();
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
