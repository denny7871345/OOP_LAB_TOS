#include "stone.hpp"
#include "Util/Time.hpp"
#include "Util/Transform.hpp"

#include "config.hpp"

void Stone::Start(int row,int column){
    //srand( time(NULL) );
    m_GiraffeText =
        std::make_shared<GiraffeText>("../assets/fonts/Inter.ttf", 10);
    m_GiraffeText->SetZIndex(this->GetZIndex() + 1);
    m_GiraffeText->Start();
    this->AddChild(m_GiraffeText);
    m_row = row;
    m_column = column;
    m_Transform.translation = glm::vec2{-225 + (75 * m_row + 37.5), 37.5 + 78 * m_column };
}

void Stone::Update() {
    static glm::vec2 dir = {0, 0};
    auto &pos = m_Transform.translation;
    if(pos.y > -350 + 78 * m_column + 37.5){
        dir.y -= 0.01;
    }else {
        m_Transform.translation.y = -350 + 78 * m_column + 37.5;
        dir.y = 0;
    }
    auto delta = static_cast<float>(Util::Time::GetDeltaTime());
    Util::Transform deltaTransform{
        dir * delta * 100.0F, 2 * delta,
        glm::vec2(0.5, 0.5) };

    pos += deltaTransform.translation;
    this->Draw();
    m_GiraffeText->Update(m_Transform);
}
