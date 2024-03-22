#ifndef STONE_HPP
#define STONE_HPP


#include "AnimatedCharacter.hpp"
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Type.hpp"
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
#include "Util/Image.hpp"
#include "GiraffeText.hpp"

class Stone : public AnimatedCharacter {

public:
    enum class state{
        Falling,
        Keeping,
        Dragging
    };
    Stone(std::vector<std::string>& AnimationPaths) : AnimatedCharacter(AnimationPaths){
        m_Animation->SetLooping(false);
        m_Animation->Pause();
    }
    void Update();

    void Start(int row,int column,std::vector<int> TypeGeneration);
    void Generate(int row,int column,std::vector<int> TypeGeneration);

    state GetState(){
        return m_state;
    }
    void SetDragging(bool drag);
    void Change(const std::shared_ptr<Stone>& target){
        int tempRow = m_row , tempColumn = m_column;
        m_row = target->GetRow();
        m_column = target->GetColumn();
        target->SetPos(tempRow,tempColumn);
    }
    [[nodiscard]] int GetRow() const { return m_row;  }
    [[nodiscard]] int GetColumn() const { return m_column;  }

    void SetPos(int row,int column);
    Type::Element_type GetType();
    void SetFalling();

    void TurnType(Type::Element_type target, bool powerup);
private:
    state m_state;
    int m_row;
    int m_column;
    Type m_type;

};

#endif
