#ifndef BACKGROUND_IMAGE_HPP
#define BACKGROUND_IMAGE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class BackgroundImage : public Util::GameObject {

public:
    BackgroundImage() : GameObject(
              std::make_unique<Util::Image>("../assets/sprites/background/base5.png"), -10) {
        m_Transform.scale = glm::vec2(1, 1);
        m_Transform.translation = glm::vec2{0,-155};
    }

    void NextPhase(const int phase) {
        auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        temp->SetImage(ImagePath(phase));
    }

private:
    inline std::string ImagePath(const int phase) {
        return  "BG.jpg";
    }
};

#endif //BACKGROUND_IMAGE_HPP
