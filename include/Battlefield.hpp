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

class Battlefield{
public:
    Battlefield();

protected:
    std::vector<std::shared_ptr<Wave>> m_waves;
};

class sample : public Battlefield{
public:
    sample();
};
#endif // BATTLEFIELD_HPP
