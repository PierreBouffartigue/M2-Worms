#include <iostream>
#include "IButton.h"

IButton::IButton() {
    m_onHoverStart = [this](auto &&btn) { onHoverStart(std::forward<decltype(btn)>(btn)); };
    m_onHoverEnd = [this](auto &&btn) { onHoverEnd(std::forward<decltype(btn)>(btn)); };
    m_onClick = [this](auto &&btn) { onClick(std::forward<decltype(btn)>(btn)); };
}

void IButton::hover(bool isHovered) {
    if (m_isActive) {
        if (isHovered && !m_isHovered) {
            std::invoke(m_onHoverStart, this);
        } else if (!isHovered && m_isHovered) {
            std::invoke(m_onHoverEnd, this);
        }
        m_isHovered = isHovered;
    }
}

void IButton::click() {
    if (m_isActive)
        std::invoke(m_onClick, this);
}

void IButton::setOnHover(const IButton::EventType &onHoverStart, const IButton::EventType &onHoverEnd) {
    m_onHoverStart = onHoverStart;
    m_onHoverEnd = onHoverEnd;
}

void IButton::setOnClick(const IButton::EventType &onClick) {
    m_onClick = onClick;
}

void IButton::onHoverStart(IButton *button) {
    std::cout << "On hover start" << std::endl;
}

void IButton::onHoverEnd(IButton *button) {
    std::cout << "On hover end" << std::endl;
}

void IButton::onClick(IButton *button) {
    std::cout << "On click" << std::endl;
}
