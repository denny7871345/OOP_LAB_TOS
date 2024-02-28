#include "AnimatedCharacter.hpp"


AnimatedCharacter::AnimatedCharacter(const std::vector<std::string>& AnimationPaths) {
    m_Animation = std::make_shared<Util::Animation>(AnimationPaths, false, 500, false, 0);
    SetDrawable(m_Animation);
    m_Animation->Play();
    m_Animation->SetLooping(true);
}

bool AnimatedCharacter::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Animation);
        return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}
