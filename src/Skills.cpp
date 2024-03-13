#include "Member.hpp"
#include "Enchant.hpp"
int Boom::StoneBreak(Type::Element_type Lvalue,bool powerup) {
    m_Enchant->StoneBreak(Lvalue);
    m_Enchant->GenerateFall(powerup);
}
