#pragma once

#include <string>
#include <cassert>
#include <chrono>
#include "SFML/Graphics.hpp"
#include "SortState.h"

template<typename T, typename U>
inline U translate(U val, U val_l, U val_h, T low, T high)
{
    return low + (high - low) * ((U) (val - val_l) / (val_h - val_l));
}

class SortRenderer
{
private:
    statePtr m_sortState;
    sf::RenderWindow *m_window;
    sf::Vector2i m_size;

    static constexpr char* s_fontName = "res/BebasNeue-Regular.otf";
    sf::Font m_font;

    static sf::Color BackgroundClr;
    static sf::Color ForegroundClr;
    static sf::Color TextClr;
    static sf::Color CurrentElemClr;
    static sf::Color NextElemClr;
    static sf::Color SectionClr;
    static sf::Color FontClr;
    
    void RenderText(const std::string& text, sf::Vector2f pos);
    void RenderBlocks();
    void RenderOverlay();

    void handleEvent(sf::Event& e);
public:
    SortRenderer();
    SortRenderer(int width, int height);

    void initSortState(statePtr state);

    void startRender();
};