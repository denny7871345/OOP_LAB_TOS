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
    Util::Root m_Root;
};

#endif
