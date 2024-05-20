#include "Util/GameObject.hpp"

namespace Util {

void GameObject::Draw() {
    if (!m_Visible) {
        return;
    }

    m_Drawable->Draw(m_Transform, m_ZIndex);
}

void GameObject::SetTranslation(float x, float y) {
    m_Transform.translation = {x,y};
}

} // namespace Util
