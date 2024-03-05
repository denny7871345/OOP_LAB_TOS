#include "Enchant.hpp"
#include "Util/input.hpp"
#include "Util/SFX.hpp"
#include <cmath>
void Enchant::Start() {
    m_row = 6 , m_column = 5;
    m_Array.resize(m_row);
    for (int i = 0; i < m_row; ++i) {
        m_Array[i].resize(m_column);
        for (int j = 0; j < m_column; ++j) {
            m_Array[i][j] = std::make_shared<Stone>(); // 使用 make_shared 創建共享指標
            m_Array[i][j]->Start(i,j);
        }
    }
    m_state = state::Keeping;
}

void Enchant::Update() {

    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_column; ++j) {
            if(m_Array[i][j] != nullptr){
                m_Array[i][j]->Update();
            }
        }
    }
    switch (m_state) {
    case state::Keeping:
        if (Util::Input::IsKeyDown(Util::Keycode::R)) {
            StoneTurn(Type::Element_type::Fire,Type::Element_type::Water,0,true);
        }
        if (Util::Input::IsKeyDown(Util::Keycode::E)){
            auto cursorPos = Util::Input::GetCursorPosition();
            int i = std::floor((cursorPos.x + 225 ) / 75) , j =  std::floor((cursorPos.y + 350) / 78);
            if(i<=m_column && j<=4 && i>=0 && j>=0){
                m_Array[i][j]->SetDragging(true);
                m_StartPos = glm::vec2(i,j);
                m_NowPos = m_StartPos;
                LOG_DEBUG("you got the {} m_row,{} m_column Stone",i+1,j+1);
                m_state = state::Dragging;
            }
        }
        break;
    case state::Dragging:
        if (Util::Input::IsMouseMoving()){
            auto cursorPos = Util::Input::GetCursorPosition();
            int i = std::floor((cursorPos.x + 225 ) / 75) , j =  std::floor((cursorPos.y + 350) / 78);
            if(i>m_column) i=m_column; if(i<0) i=0; if(j>4)j=4;if(j<0)j=0;
            if(!(m_StartPos == glm::vec2(i,j))){
                LOG_DEBUG("Let's Moving to [{},{}] from [{},{}]",i+1,j+1,m_NowPos.x+1,m_NowPos.y+1);
                Change(m_StartPos,glm::vec2 (i,j));
                m_NowPos = glm::vec2 (i,j);
                m_state = state::Moving;
                break;
            }
        }
        if (Util::Input::IsKeyUp(Util::Keycode::E)){
            m_Array[int(m_StartPos.x)][int(m_StartPos.y)]->SetDragging(false);
            m_state = state::Keeping;
            LOG_DEBUG("you put the {} m_row,{} m_column Stone",m_StartPos.x+1,m_StartPos.y+1);
        }
        break;
    case state::Moving:

        if (Util::Input::IsMouseMoving()){
            auto cursorPos = Util::Input::GetCursorPosition();
            int i = std::floor((cursorPos.x + 225 ) / 75) , j =  std::floor((cursorPos.y + 350) / 78);
            if(i>m_column) i=m_column; if(i<0) i=0; if(j>4)j=4;if(j<0)j=0;
            if (!(m_NowPos == glm::vec2(i, j))) {
                Change(m_NowPos, glm::vec2(i, j));
                m_NowPos = glm::vec2(i, j);
                LOG_DEBUG("You are now at [{},{}]", int(m_NowPos.x) + 1,
                          int(m_NowPos.y) + 1);
                break;
            }
        }
        if (Util::Input::IsKeyUp(Util::Keycode::E)){
            m_Array[int(m_StartPos.x)][int(m_StartPos.y)]->SetDragging(false);
            m_EndPos = m_NowPos;
            m_state = state::Checking;
        }
        break;
    case state::Checking:
        for (int i = 0; i < m_row; ++i) {
            for (int j = 0; j < m_column; ++j) {
                if(m_Array[i][j] != nullptr)m_Array[i][j]->SetDragging(false);
            }
        }

        while(CheckMatch()){

        }

        if(CheckFull()){
            m_state = state::Keeping;
        }else{
            m_state = state::Falling;
        }

        break;
    case state::Falling:
        ShowEnchant();
        DoFall();
        ShowEnchant();
        GenerateFall();
        ShowEnchant();
        if(CheckFall())m_state = state::Checking;
        break;
    }
}

void Enchant::Change(glm::vec2 pos1,glm::vec2 pos2){
    static auto SFX = Util::SFX("../assets/audio/Click.wav");
    SFX.Play();
    m_Array[pos1.x][pos1.y]->Change(m_Array[pos2.x][pos2.y]);
    std::swap(m_Array[int(pos1.x)][int(pos1.y)], m_Array[int(pos2.x)][int(pos2.y)]);
}

bool Enchant::CheckMatch() {
    for(int i=0;i<m_row;++i){
        for(int j=0;j<m_column;j++){
            //LOG_DEBUG("Checking [{},{}]",i+1,j+1);
            if(m_Array[i][j] != nullptr){
                std::vector<std::shared_ptr<Stone>> breakList;
                breakList.push_back(m_Array[i][j]);
                while (j + breakList.size() < m_column){
                    if(m_Array[i][j+breakList.size()] != nullptr){
                        if(m_Array[i][j]->GetType() == m_Array[i][j+breakList.size()]->GetType()){
                            breakList.push_back(m_Array[i][j+breakList.size()]);
                        }else{
                            break;
                        }
                    }else{
                        break;
                    }
                }
                if(breakList.size() >= 3){
                    for(int k=0;k<breakList.size();k++){
                        LOG_DEBUG("erase [{},{}]",breakList[k]->GetRow()+1,breakList[k]->GetColumn()+1);
                        m_Array[i][j+k].reset();
                    }
                    return true;
                }else{
                    //LOG_DEBUG("breakList has {} blocks",breakList.size());
                }
            }
        }
    }
    for(int i=0;i<m_row;++i) {
        for (int j = 0; j < m_column; j++) {
            // LOG_DEBUG("Checking [{},{}]",i+1,j+1);
            if (m_Array[i][j] != nullptr) {
                std::vector<std::shared_ptr<Stone>> breakList;
                breakList.push_back(m_Array[i][j]);
                while (i + breakList.size() < m_row) {
                    if (m_Array[i + breakList.size()][j] != nullptr) {
                        if (m_Array[i][j]->GetType() ==
                            m_Array[i + breakList.size()][j]->GetType()) {
                            breakList.push_back(
                                m_Array[i + breakList.size()][j]);
                        } else {
                            break;
                        }
                    } else {
                        break;
                    }
                }
                if (breakList.size() >= 3) {
                    for (int k = 0; k < breakList.size(); k++) {
                        LOG_DEBUG("erase [{},{}]", breakList[k]->GetRow() + 1,
                                  breakList[k]->GetColumn() + 1);
                        m_Array[i+k][j].reset();
                    }
                    return true;
                } else {
                    // LOG_DEBUG("breakList has {} blocks",breakList.size());
                }
            }
        }
    }
    return false;
}

void Enchant::DoFall() {
    for(int i=0;i<m_row;++i) {
        for(int loop=0;loop<4;loop++) {
            for (int j = 1; j < m_column; j++) {
                if (m_Array[i][j] != nullptr) {
                    if (m_Array[i][j - 1] == nullptr) {
                        m_Array[i][j - 1] = m_Array[i][j];
                        m_Array[i][j - 1]->SetPos(i, j - 1);
                        m_Array[i][j-1]->SetFalling();
                        m_Array[i][j].reset();
                    }
                }
            }
        }
    }
    for(int i=0;i<m_row;++i) {
        for (int j = 0; j < m_column; j++) {

        }
    }

}

void Enchant::ShowEnchant() {
    for(int i=0;i<m_column;++i) {
        std::string lists = "";
        for (int j = 0; j < m_row; j++) {
            if(m_Array[j][4-i] != nullptr){
                lists += "V";
            }else{
                lists += "X";
            }
        }
        LOG_DEBUG("{}",lists);
    }
    LOG_DEBUG("-----------");
}

void Enchant::GenerateFall() {
    for(int i=0;i<m_row;i++){
        for(int j=0;j<m_column;j++){
            if(m_Array[i][j] == nullptr){
                m_Array[i][j] = std::make_shared<Stone>(); // 使用 make_shared 創建共享指標
                m_Array[i][j]->Generate(i,j);
            }
        }
    }

}

bool Enchant::CheckFall() {
    for(int i=0;i<m_row;i++) {
        for (int j = 0; j < m_column; j++) {
            if(m_Array[i][j]->GetState() != Stone::state::Keeping){
                return false;
            }
        }
    }
    return true;
}

bool Enchant::CheckFull(){
    for(int i=0;i<m_row;i++){
        for(int j=0;j<m_column;j++){
            if(m_Array[i][j] == nullptr){
                return false;
            }
        }
    }
    return true;
}