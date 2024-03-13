#include "Member.hpp"
#include "Enchant.hpp"

int Boom::StoneBreak(Type::Element_type Lvalue,bool powerup) {
    int count = m_Enchant->StoneBreak(Lvalue);
    m_Enchant->GenerateFall(powerup);
    return count;
}

void StoneTurn::Turn(Type::Element_type Lvalue, Type::Element_type Rvalue, bool powerup) {
    m_Enchant->StoneTurn(Lvalue,Rvalue,0,powerup);
}