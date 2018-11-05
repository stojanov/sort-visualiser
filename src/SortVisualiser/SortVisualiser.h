#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <ratio>

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
    SortAlgoT m_SortAlgo;
    std::chrono::high_resolution_clock::time_point m_start;
    std::chrono::high_resolution_clock::time_point m_end;
public:
    SortVisualiser(int width, int height, int samples, float delay, std::string algoName)
    :   m_samples(samples), 
        m_delay(1000 * delay), 
        m_arr(new int[samples + 1]), 
        m_WIDTH(width),
        m_HEIGHT(height)
    {

        m_name = "Algorithm : " +  algoName;

        m_SortAlgo = SortAlgoT(m_arr, m_samples);

        init_sort_algo();

        spawn_window();

        exit(0);
    }

    void start_sorting()
    {
        m_array_changes = 0;
        
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
                    std::chrono::microseconds(m_delay)
                );
            }
        );
    }

    void sort_func()
    {
        randomize();
        m_start = std::chrono::high_resolution_clock::now();
        m_finished = false;
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

        if (!BebasNeue.loadFromFile("res/BebasNeue-Regular.otf"))
        {
            std::cout << "Error loading font.\n";
            exit(0);
        }

        std::string DelayStr("Delay : " + std::to_string((m_delay * 1.f) / 1000) + " ms");
        std::string SamplesStr("Array length : " + std::to_string(m_samples));   

        sf::RenderWindow window(
            sf::VideoMode(m_WIDTH, m_HEIGHT),
            "Sort"
        );

        window.setVerticalSyncEnabled(true);

        while (window.isOpen())
        {
            sf::Event e;
            
            while (window.pollEvent(e))
            {
                switch (e.type)
                {
                    case sf::Event::Closed: window.close(); break;
                    case sf::Event::KeyPressed:
                        switch (e.key.code)
                        {
                            case sf::Keyboard::S: 
                                if(m_finished)
                                {
                                    start_sorting();
                                }
                            break;
                        }
                    break;
                }
            }

            window.clear(BackgroundClr);

            std::string ArrayInsertStr("Array changes : " + std::to_string(m_array_changes));

            displayText(ArrayInsertStr, sf::Vector2f(20, 10), TextClr, BebasNeue, &window);
            displayText(DelayStr, sf::Vector2f(20, 28), TextClr, BebasNeue, &window);
            displayText(m_name, sf::Vector2f(20, 46), TextClr, BebasNeue, &window);
            displayText(SamplesStr, sf::Vector2f(20, 64), TextClr, BebasNeue, &window);

            if(!m_finished)
            {
                m_end = std::chrono::high_resolution_clock::now();
            }

            std::chrono::duration<float, std::milli> time_passed = m_end - m_start;

            std::string TimePassedStr("Time passed :" + std::to_string((float) time_passed.count()) + " ms");
            displayText(TimePassedStr, sf::Vector2f(300, 10) ,TextClr, BebasNeue, &window);

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

                window.draw(rect);
            }
            
            window.display();
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
                std::chrono::microseconds(m_delay)
            );
        }
    }

    ~SortVisualiser()
    {
        delete []m_arr;
    }
};