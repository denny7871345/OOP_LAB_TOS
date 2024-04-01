#ifndef TYPE_HPP
#define TYPE_HPP
#include "Util/Color.hpp"
#include <random>
#include <utility>
class Type {
public:
    enum Race_type{
        Protoss,
        Demon,
        Mortal,
        Beast,
        Dragon,
        Fairy
    };
    enum Element_type{
        Fire,
        Water,
        Grass,
        Light,
        Dark,
        Heart,
        NUM_ELEMENTS
    };
    static Type::Element_type TypeList(int index){
        static Element_type elements[NUM_ELEMENTS] = {Fire, Water, Grass, Light, Dark, Heart};
        return elements[index];
    }
    void RandomTypeGenerator(std::vector<int> lists) {
        std::random_device rd;
        std::mt19937 gen(rd());
        // 分布器
        std::uniform_int_distribution<> dis(1, 120);
        int randomIndex = dis(gen);
        int num=0;
        m_powerup = false;
        static Element_type elements[NUM_ELEMENTS] = {Fire, Water, Grass, Light, Dark, Heart};
        for(int i=0;i<NUM_ELEMENTS;i++){
            num += lists[i];
            if(randomIndex < num){
                m_type = elements[i];
                //LOG_DEBUG("Num is {} and it comes out {} block",randomIndex,TypeString());
                return;
            }
        }
    }
    bool IsPowerUp(){return m_powerup;}
    static int FindIndex(Element_type target){
        static Element_type elements[NUM_ELEMENTS] = {Fire, Water, Grass, Light, Dark, Heart};
        return std::find(elements,elements+NUM_ELEMENTS,target) - elements;
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
                return "Heart";
        }
    }
    static std::string TypeString(Element_type target) {
        switch(target) {
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
            return "Heart";
        }
    }
    Util::Colors TypeColor(){
        if(m_powerup) return Util::Colors::WHITE;
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
            return Util::Colors::PINK;
        }
    }
    Element_type GetType(){
        return m_type;
    }
    void SetType(Element_type target,bool powerup){
        int flag = false;
        if(m_powerup) flag = true;
        m_type = target;
        m_powerup = (powerup || flag) ;
    }
    std::vector<std::string> GetStoneNormalImage(){
        std::string typeName="";
        switch(m_type) {
            case Element_type::Fire:
                typeName += "f";
                break;
            case Element_type::Water:
                typeName +="w";
                break;
            case Element_type::Grass:
                typeName +="p";
                break;
            case Element_type::Light:
                typeName +="l";
                break;
            case Element_type::Dark:
                typeName +="d";
                break;
            default:
                typeName +="h";
                break;
        }
        if(m_powerup) typeName += "+";
        return {"../assets/sprites/Stones/" + typeName + ".png",
                "../assets/sprites/Stones/" + typeName + "_.png"};
    }
private:
    Element_type m_type;
    bool m_powerup;
};
#endif
