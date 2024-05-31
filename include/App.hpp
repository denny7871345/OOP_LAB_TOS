#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Root.hpp"
#include "BackgroundImage.hpp"
#include "Battlefield.hpp"
#include "AnimatedCharacter.hpp"
#include "Cat.hpp"
#include "Giraffe.hpp"
#include "GiraffeText.hpp"
#include "Enchant.hpp"
#include "UI.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    [[nodiscard]] State GetCurrentState() const { return m_CurrentState; }

    void Start();
    void Update();
    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    State m_CurrentState = State::START;
    std::shared_ptr<BattleSystem> m_battleSystem = std::make_shared<BattleSystem>();
    std::shared_ptr<Enchant> m_enchant = std::make_shared<Enchant>();
    std::shared_ptr<Giraffe> m_Giraffe = std::make_shared<Giraffe>();
    //    std::shared_ptr<GiraffeText> m_GiraffeText =
    //    std::make_shared<GiraffeText>();

    std::shared_ptr<BackgroundImage> m_BG = std::make_shared<BackgroundImage>();
    std::shared_ptr<BattlefieldIMG> m_BG2 = std::make_shared<BattlefieldIMG>();
    Util::Root m_Root;
    std::shared_ptr<UI> m_UI = std::make_shared<UI>();
    std::shared_ptr<Choice> m_test = std::make_shared<Choice>("../assets/sprites/Characters/107n.png",1,1);
    std::shared_ptr<Choice> m_test1 = std::make_shared<Choice>("../assets/sprites/Characters/107n.png",2,1);
    std::shared_ptr<Choice> m_test2 = std::make_shared<Choice>("../assets/sprites/Characters/107n.png",3,1);
};

#endif
