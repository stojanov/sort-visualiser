#include "SortRenderer.h"

#include <iostream>

sf::Color SortRenderer::BackgroundClr = sf::Color(34, 24, 28);
sf::Color SortRenderer::ForegroundClr = sf::Color(255, 255, 255);
sf::Color SortRenderer::TextClr = sf::Color(202, 207, 214);

sf::Color SortRenderer::CurrentElemClr = sf::Color(255, 0, 0);
sf::Color SortRenderer::SectionClr = sf::Color(200, 200, 200);

sf::Color SortRenderer::FontClr = sf::Color(255, 255, 255);

SortRenderer::SortRenderer() {}

SortRenderer::SortRenderer(int width, int height)
{
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), "Sort Visualiser");
    m_size = { width, height };

    assert(m_font.loadFromFile(s_fontName));

    m_window->setActive(false);
    m_window->setVerticalSyncEnabled(true);
    m_window->setFramerateLimit(60);
}

void SortRenderer::initSortState(statePtr state) 
{
    m_sortState = state; 
}

void SortRenderer::handleEvent(sf::Event& e)
{
    switch (e.type) 
    {
        case sf::Event::Closed: m_window->close(); break;
        case sf::Event::KeyPressed:
            switch (e.key.code)
            {
                case sf::Keyboard::E:
                    m_window->close(); break;
            }
    }
}

void SortRenderer::RenderText(const std::string& txt, sf::Vector2f pos)
{
    static sf::Text renderText;

    renderText.setFont(m_font);
    renderText.setPosition(pos);
    renderText.setFillColor(FontClr);
    renderText.setCharacterSize(18);
    renderText.setString(txt.c_str());

    m_window->draw(renderText);
}

void SortRenderer::RenderOverlay()
{
    const static std::string arrLenStr = "Array length: " + std::to_string(m_sortState->samples);
    const static std::string delayStr = "Delay: " + std::to_string((m_sortState->delay * 1.f) / 1000) + "ms";
    
    RenderText("Array changes: " + std::to_string(m_sortState->arrayChanges), { 20, 10 });
    RenderText(delayStr, { 20, 28 });
    RenderText(arrLenStr, { 20, 64 });
}

void SortRenderer::RenderBlocks()
{
    static constexpr int TEXT_OFFSET = 100;
    static float blockWidth = (float) m_size.x / m_sortState->samples;
    static sf::RectangleShape rect;
    static auto transl = translate<int, float>;

    for (int i = 0; i < m_sortState->samples; i++)
    {
        const float blockHeight = transl(
            m_sortState->sortingArray[i],
            0, m_sortState->samples,
            0, m_size.y - TEXT_OFFSET
        );

        const int id = i;

        if (id == m_sortState->currentId) 
        {
            rect.setFillColor(CurrentElemClr);
        }
        else if (i > m_sortState->sectionStart && i <= m_sortState->sectionEnd)
        {
            rect.setFillColor(SectionClr);
        } else
        {
            rect.setFillColor(ForegroundClr);
        }

        rect.setSize({ blockWidth, -1 * blockHeight });
        rect.setPosition(i * blockWidth, m_size.y);

        m_window->draw(rect);
    }
}

void SortRenderer::startRender()
{
    while (m_window->isOpen()) 
    {
        sf::Event e;

        while (m_window->pollEvent(e)) 
        {
            handleEvent(e);
        }

        m_window->clear(BackgroundClr);

        RenderBlocks();
        RenderOverlay();

        m_window->display();
    }
}
