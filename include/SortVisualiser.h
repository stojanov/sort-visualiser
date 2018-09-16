#ifndef SORT_VIS_H
#define SORT_VIS_H

#include "SFML/Graphics.hpp"
#include <random>
#include <chrono>
#include <thread>

#include "Sort.h"


// Copied from another project i'm working on
template<typename T, typename rtn_type>
rtn_type translate(rtn_type val, rtn_type val_l, rtn_type val_h, T low, T high)
{
    return low + (high - low) * ((rtn_type) (val - val_l) / (val_h - val_l));
}

void displayText(std::string &text, sf::Vector2f pos, sf::Color &clr, sf::Font &font, sf::RenderWindow *window)
{
    sf::Text renderText;

    renderText.setFont(font);
    renderText.setPosition(pos);
    renderText.setColor(clr);
    renderText.setCharacterSize(18);
    renderText.setString(text.c_str());

    window->draw(renderText);
}

template<typename SortAlgoT>
class SortVisualiser
{
private:
    int *m_arr;
    int m_samples;
    int m_delay;
    int m_array_changes{0};
    int m_current_sortel{0};
    int m_next_id{0};
    int m_WIDTH;
    int m_HEIGHT;
    int m_section_first{0};
    int m_section_last{0};
    bool m_finished{true};
    std::string m_name;
    sf::RenderWindow *m_mainWindow;
    SortAlgoT m_SortAlgo;
public:
    SortVisualiser(int width, int height, int samples, int delay, std::string algoName)
    :   m_samples(samples), 
        m_delay(delay), 
        m_arr(new int[samples + 1]), 
        m_WIDTH(width),
        m_HEIGHT(height)
    {
        
        m_name = "Algorithm : " +  algoName;

        m_SortAlgo = SortAlgoT(m_arr, m_samples);

        m_mainWindow = new sf::RenderWindow(
            sf::VideoMode(m_WIDTH, m_HEIGHT),
            "Sort"
        );

        init_sort_algo();

        std::thread window_thread(
            [&] () 
            {
                spawn_window();
            }
        );

        window_thread.join();
        exit(0);
    }

    void start_sorting()
    {
        std::thread sort_thread(
            [&] () 
            {
                sort_func();
            }
        );
        
        sort_thread.detach();
    }

    void init_sort_algo()
    {
        m_SortAlgo.assign_swap_func(
            [&] (int id, int nextid, int sstart, int send) 
            {
                m_array_changes++;
                m_current_sortel = id;
                m_next_id = nextid;
                m_section_first = sstart;
                m_section_last = send;

                std::this_thread::sleep_for(
                    std::chrono::milliseconds(m_delay)
                );
            }
        );
    }

    void sort_func()
    {
        randomize();
        m_SortAlgo.sort();
        m_finished = true;
    }

    void spawn_window()
    {
        sf::Color BackgroundClr(34, 24, 28);
        sf::Color ForegroundClr(214, 229, 227);
        sf::Color TextClr(202, 207, 214);

        sf::Color CurrentElemClr(30, 45, 36);
        sf::Color NextElemClr(181, 217, 156);
        sf::Color SectionClr(227, 151, 116);

        const float block_width = (float) m_WIDTH / m_samples;
     
        auto transl = translate<int, float>;

        sf::RectangleShape rect;

        sf::Font BebasNeue;

        if (!BebasNeue.loadFromFile("BebasNeue_Regular.otf"))
        {
            std::cout << "Error loading font.\n";
            exit(0);
        }

        std::string DelayStr("Delay : " + std::to_string(m_delay) + "ms");
        std::string SamplesStr("Array length : " + std::to_string(m_samples));

        while (m_mainWindow->isOpen())
        {
            sf::Event e;
            
            while (m_mainWindow->pollEvent(e))
            {
                if (e.type == sf::Event::Closed)
                    m_mainWindow->close();

                if (e.type == sf::Event::KeyPressed)
                {
                    if (e.key.code == sf::Keyboard::S)
                    {
                        if (m_finished) 
                        {
                            m_finished = false;
                            start_sorting();
                        }
                    }
                }
            }

            m_mainWindow->clear(BackgroundClr);

            std::string ArrayInsertStr("Array changes : " + std::to_string(m_array_changes));

            displayText(ArrayInsertStr, sf::Vector2f(20, 10), TextClr, BebasNeue, m_mainWindow);
            displayText(DelayStr, sf::Vector2f(20, 28), TextClr, BebasNeue, m_mainWindow);
            displayText(m_name, sf::Vector2f(20, 48), TextClr, BebasNeue, m_mainWindow);
            displayText(SamplesStr, sf::Vector2f(20, 64), TextClr, BebasNeue, m_mainWindow);

            const int TEXT_OFFSET = 100;
            for(int i = 0; i < m_samples; i++) 
            {
                float block_height = transl(m_arr[i], 0, m_samples, 0, m_HEIGHT - TEXT_OFFSET);
                
                if (i - 1 == m_current_sortel)
                {
                    rect.setFillColor(CurrentElemClr);
                }
                else if (i - 1 == m_next_id)
                {
                    rect.setFillColor(NextElemClr);
                }
                else
                {
                    if (i > m_section_first && i < m_section_last)
                        rect.setFillColor(SectionClr);
                    else
                        rect.setFillColor(ForegroundClr);
                }

                rect.setSize(
                    sf::Vector2f(block_width, -1 * block_height)
                );

                rect.setPosition(i*block_width, m_HEIGHT);

                m_mainWindow->draw(rect);
                
            }
            

            m_mainWindow->display();
        }
    }

    // Helper
    void printarr()
    {
        m_SortAlgo.printarr();
    }

    void randomize()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0, m_samples);
        
        for(int i = 0; i < m_samples; i++)
        {
            m_arr[i] = (int) dist(mt);
            std::this_thread::sleep_for(
                std::chrono::milliseconds(m_delay)
            );
        }
    }

    ~SortVisualiser()
    {
        delete []m_arr;
    }
};

#endif