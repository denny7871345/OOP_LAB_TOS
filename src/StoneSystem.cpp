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
            std::default_random_engine rng(std::random_device{}());
            std::shuffle(lists.begin(),lists.end(),rng);
            lists[i]->TurnType(RValue,powerup);
        }
    }
}

void Stone::Start(int row,int column,std::vector<int> TypeGeneration){
    m_type.RandomTypeGenerator(std::move(TypeGeneration));
    m_GiraffeText =
        std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf", 100);
    m_GiraffeText->SetZIndex(this->GetZIndex() + 1);
    m_GiraffeText->Start();
    m_GiraffeText->SetColor(m_type.TypeColor());
    m_GiraffeText->SetText(m_type.TypeString()); //此行有問題
    m_row = row;
    m_column = column;
    m_state = state::Keeping;
}

void Stone::Generate(int row,int column,std::vector<int> TypeGeneration) {
    m_row = row;
    m_column = column;
    LOG_DEBUG("({},{})",m_row+1,m_column+1);
    m_type.RandomTypeGenerator(std::move(TypeGeneration));
    m_GiraffeText =
        std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf", 100);
    m_GiraffeText->SetZIndex(this->GetZIndex() + 1);
    m_GiraffeText->Start();
    m_GiraffeText->SetColor(m_type.TypeColor());
    m_GiraffeText->SetText(m_type.TypeString()); //此行有問題

    m_Transform.translation = glm::vec2{-225 + (75 * m_row + 37.5), 37.5 + 78 * m_column };
    m_state = state::Falling;
}


void Stone::TurnType(Type::Element_type target, bool powerup) {
    m_type.SetType(target,powerup) ;
}
