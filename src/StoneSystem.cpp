#include "Enchant.hpp"
#include "Stone.hpp"
void Enchant::SetTypeGeneration(std::vector<int> lists){
    m_TypeGeneration = lists;
}

std::vector<int> Enchant::GetTypeGeneration() {
    return m_TypeGeneration;
}

void Enchant::StoneTurn(Type::Element_type LValue, Type::Element_type RValue, int howmany,bool powerup) {
    if(howmany ==0){ //0 = 全部符石，非0為隨機X個石頭
        for (int i = 0; i < m_row; ++i) {
            for (int j = 0; j < m_column; ++j) {
                if(m_Array[i][j]->GetType() == LValue ) m_Array[i][j]->TurnType(RValue,powerup);
            }
        }
    }else{
        std::vector<std::shared_ptr<Stone>> lists;
        for (int i = 0; i < m_row; ++i) {
            for (int j = 0; j < m_column; ++j) {
                if(m_Array[i][j]->GetType() == LValue ) lists.push_back(m_Array[i][j]);
            }
        }
        for(int i=0;i<howmany;i++){
            std::random_device rd;
            std::mt19937 gen(rd());
            // 分布器
            std::uniform_int_distribution<> dis(0, int(lists.size()));
            int randomIndex = dis(gen);
            lists[randomIndex]->TurnType(RValue,powerup);
        }
    }
}

void Stone::TurnType(Type::Element_type target, bool powerup) {
    m_type.SetType(target,powerup) ;
}