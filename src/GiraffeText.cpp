#include "GiraffeText.hpp"

#include "Util/Color.hpp"
#include "Util/Time.hpp"
#include "Util/Transform.hpp"

void GiraffeText::Start() {

    m_Text = std::make_unique<Util::Text>(m_Font, m_Size, ".",
                                          Util::Color::FromRGB(255, 0, 0));
    SetDrawable(m_Text);
}

void GiraffeText::Update() {

    //m_Text->SetText(fmt::format("{:.02f}", 1.0F / Util::Time::GetDeltaTime()));
    this->Draw();
}

void GiraffeText::Update(Util::Transform follows) {
    m_Transform = follows;
    m_Transform.scale = glm::vec2 (0.4,0.4);
    m_Size = 1;
    this->Draw();
}

void GiraffeText::SetText(const std::string text) {
    m_Text->SetText(fmt::format(text) );

}

void GiraffeText::SetColor(Util::Colors colors) {
    m_Text->SetColor(Util::Color::FromName(colors) );
}