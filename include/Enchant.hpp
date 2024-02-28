#ifndef ENCHANT_HPP
#define ENCHANT_HPP

#include "Stone.hpp"
#include "Util/GameObject.hpp"
class Enchant:public Util::GameObject{
public:
    void Update();
    void Start();
private:
    std::vector<std::vector<std::shared_ptr<Stone>>> m_Array;
};


#endif
