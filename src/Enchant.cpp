#include "Enchant.hpp"
#include "Util/input.hpp"
#include "Util/SFX.hpp"
#include <cmath>
void Enchant::Start() {
    int row = 6 , column = 5;
    m_Array.resize(row);
    for (int i = 0; i < row; ++i) {
        m_Array[i].resize(column);
        for (int j = 0; j < column; ++j) {
            m_Array[i][j] = std::make_shared<Stone>(); // 使用 make_shared 創建共享指標
            m_Array[i][j]->Start(i,j);
        }
    }
    m_state = state::Keeping;
}

void Enchant::Update() {

    int row = 6 , column = 5;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            m_Array[i][j]->Update();
        }
    }
    switch (m_state) {
    case state::Keeping:
        if (Util::Input::IsKeyDown(Util::Keycode::E)){
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                    if(m_Array[i][j]->IsBeClicked()){
                        m_Array[i][j]->SetDragging(true);
                        m_StartPos = glm::vec2(i,j);
                        m_NowPos = m_StartPos;
                        LOG_DEBUG("you got the {} row,{} column Stone",i+1,j+1);
                        m_state = state::Dragging;
                    }
                }
            }
        }
        break;
    case state::Dragging:
        if (Util::Input::IsMouseMoving()){
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                    if(m_Array[i][j]->IsBeClicked()){
                        if(!(m_StartPos == glm::vec2(i,j))){
                            LOG_DEBUG("Let's Moving to [{},{}] from [{},{}]",i+1,j+1,m_NowPos.x+1,m_NowPos.y+1);
                            Change(m_StartPos,glm::vec2 (i,j));
                            m_NowPos = glm::vec2 (i,j);
                            m_state = state::Moving;
                            break;
                        }
                    }
                }
            }
        }
        if (Util::Input::IsKeyUp(Util::Keycode::E)){
            m_Array[int(m_StartPos.x)][int(m_StartPos.y)]->SetDragging(false);
            m_state = state::Keeping;
            LOG_DEBUG("you put the {} row,{} column Stone",m_StartPos.x+1,m_StartPos.y+1);
        }
        break;
    case state::Moving:

        if (Util::Input::IsMouseMoving()){
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                    if (m_Array[i][j]->IsBeClicked()) {
                        if (!(m_NowPos == glm::vec2(i, j))) {
                            Change(m_NowPos, glm::vec2(i, j));
                            m_NowPos = glm::vec2(i, j);
                            LOG_DEBUG("You are now at [{},{}]", int(m_NowPos.x) + 1, int(m_NowPos.y) + 1);
                            break;
                        }
                    }
                }
            }
        }
        if (Util::Input::IsKeyUp(Util::Keycode::E)){
            m_Array[int(m_StartPos.x)][int(m_StartPos.y)]->SetDragging(false);
            m_EndPos = m_NowPos;
            m_state = state::Checking;
        }
        break;
    case state::Checking:
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                m_Array[i][j]->SetDragging(false);
            }
        }
        LOG_DEBUG("you are Dragging Start in the {} row,{} column",m_StartPos.x,m_StartPos.y);
        LOG_DEBUG("you are Dragging End in the {} row,{} column",m_EndPos.x,m_EndPos.y);
        m_state = state::Falling;
        break;
    case state::Falling:
        m_state = state::Keeping;
        break;
    }
}

void Enchant::Change(glm::vec2 pos1,glm::vec2 pos2){
    static auto SFX = Util::SFX("../assets/audio/Click.wav");
    SFX.Play();
    m_Array[pos1.x][pos1.y]->Change(m_Array[pos2.x][pos2.y]);
    std::swap(m_Array[int(pos1.x)][int(pos1.y)], m_Array[int(pos2.x)][int(pos2.y)]);
}