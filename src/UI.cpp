//
// Created by fungp on 2024/5/31.
//
#include "UI.hpp"
const int ImgSize = 125;
Choice::Choice(std::string path, int index, int total) {
    m_index = index;
    m_total = total;
    SetDrawable(
        std::make_shared<Util::Image>(path));
    m_Transform.translation = {0,400-ImgSize*index};
}
void Choice::Update() {
    this->Draw();
}
void UI::Start() {

}
