#ifndef TYPE_HPP
#define TYPE_HPP
#include <random>
#include <utility>
class Type {
public:
    void Start(){
        m_type = RandomTypeGenerator();
    }
    enum Element_type{
        Fire,
        Water,
        Grass,
        Light,
        Dark
    };

    Element_type RandomTypeGenerator() {
        std::random_device rd;
        std::mt19937 gen(rd());
        // 分布器
        std::uniform_int_distribution<> dis(0, 4);

        int randomIndex = dis(gen);

        switch(randomIndex) {
        case 0:
            return Element_type::Fire;
        case 1:
            return Element_type::Water;
        case 2:
            return Element_type::Grass;
        case 3:
            return Element_type::Light;
        case 4:
            return Element_type::Dark;
        default:
            // 預設為 Fire
            return Element_type::Fire;
        }
    }
     std::string TypeString() {
        switch(m_type) {
            case Element_type::Fire:
                return "Fire";
            case Element_type::Water:
                return "Water";
            case Element_type::Grass:
                return "Grass";
            case Element_type::Light:
                return "Light";
            case Element_type::Dark:
                return "Dark";
            default:
                return "Error";
        }
    }

    Util::Colors TypeColor(){
        switch(m_type) {
        case Element_type::Fire:
            return Util::Colors::RED;
        case Element_type::Water:
            return Util::Colors::BLUE;
        case Element_type::Grass:
            return Util::Colors::GREEN;
        case Element_type::Light:
            return Util::Colors::YELLOW;
        case Element_type::Dark:
            return Util::Colors::PURPLE;
        default:
            return Util::Colors::GRAY;
        }
    }
private:
    Element_type m_type;
};
#endif
