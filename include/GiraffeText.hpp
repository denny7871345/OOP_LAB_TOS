#ifndef GIRAFFE_TEXT_HPP
#define GIRAFFE_TEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

class GiraffeText : public Util::GameObject {
public:
    GiraffeText() = default;

    GiraffeText(std::string font, const int size)
        : m_Font(std::move(font)),
          m_Size(size) {}

    ~GiraffeText() override = default;

    void Start();
    void SetText(const std::string text);
    void Update();
    void Update(Util::Transform follows);
    void Update(glm::vec2 pos);
    void SetColor(Util::Colors colors);
private:
    std::string m_Font;
    int m_Size;
    std::shared_ptr<Util::Text> m_Text;
};

#endif
