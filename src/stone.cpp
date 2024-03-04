#include "stone.hpp"
#include "Util/Time.hpp"
#include "Util/Transform.hpp"
#include <cstdlib>
#include "Util/Input.hpp"
#include "config.hpp"

void Stone::Start(int row,int column){
    m_type.Start();
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

void Stone::Generate(int row,int column) {
    m_type.Start();
    m_GiraffeText =
        std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf", 100);
    m_GiraffeText->SetZIndex(this->GetZIndex() + 1);
    m_GiraffeText->Start();
    m_GiraffeText->SetColor(m_type.TypeColor());
    m_GiraffeText->SetText(m_type.TypeString()); //此行有問題
    m_row = row;
    m_column = column;
    m_Transform.translation = glm::vec2{-225 + (75 * m_row + 37.5), 37.5 + 78 * m_column };
    m_state = state::Falling;
}

void Stone::Update() {
    static glm::vec2 dir = {0, 0};
    auto &pos = m_Transform.translation;
    switch(m_state){
        case state::Falling:
            if(pos.y > -350 + 78 * m_column + 37.5){
                dir.y -= 0.01;
                break;
            }else {
                m_Transform.translation.y = -350 + 78 * m_column + 37.5;
                dir.y = 0;
                m_state = state::Keeping;
                break;
            }
        case state::Keeping:
            m_Transform.translation = glm::vec2{-225 + (75 * m_row + 37.5), -350 + 78 * m_column + 37.5 };
            break;
        case state::Dragging:
            m_Transform.translation = Util::Input::GetCursorPosition();
            break;
    }

    auto delta = static_cast<float>(Util::Time::GetDeltaTime());
    Util::Transform deltaTransform{
        dir * delta * 100.0F, 2 * delta,
        glm::vec2(0.5, 0.5) };
    pos += deltaTransform.translation;
    m_GiraffeText->SetText("(" + std::to_string(m_row+1) + "," + std::to_string(m_column+1) + ")");
    m_GiraffeText->Update(m_Transform);
    this->Draw();

}




void Stone::SetDragging(bool drag) {
    if(drag){
        m_state = state::Dragging;
    }else{
        m_state = state::Keeping;
    }
}

void Stone::SetPos(int row, int column) {
    m_row = row;
    m_column = column;
}

Type::Element_type Stone::GetType(){
    return m_type.GetType();
}

void Stone::SetFalling() {
    m_state = state::Falling;
}