#ifndef STONE_HPP
#define STONE_HPP


#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Type.hpp"
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
#include "Util/Image.hpp"
#include "GiraffeText.hpp"

class Stone : public Util::GameObject {

public:
    enum class state{
        normal,
        powerup
    };
    Stone():Util::GameObject(std::make_unique<Util::Image>("../assets/sprites/gray.png"), 5){

    }
    void Update();

    void Start(int row,int column);

private:
    type m_type = type::Fire;
    state m_state = state::normal;
    int m_row;
    int m_column;
    std::shared_ptr<GiraffeText> m_GiraffeText;
};

#endif
