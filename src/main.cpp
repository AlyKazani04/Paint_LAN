#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <cmath>


int main()
{
    sf::RenderWindow window;

    window.create(sf::VideoMode({800, 600}), "Paint", sf::Style::Default);

    sf::View drawingView(sf::FloatRect({0.f, 0.f}, {(float)window.getSize().x, (float)window.getSize().y}));
    window.setView(drawingView);

    sf::Clock clock;

    std::vector<std::vector<sf::Vector2f>> strokes;
    std::vector<sf::Vector2f> currentStroke;

    float thickness = 2.f;

    while(window.isOpen())
    {
        while(const std::optional<sf::Event> event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if(event->is<sf::Event::MouseButtonReleased>() && event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)
            {
                if(!currentStroke.empty())
                {
                    strokes.push_back(currentStroke);
                    currentStroke.clear();
                }
            }
        }

        // Update
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
            currentStroke.push_back(worldPos);
        }
    
        // Draw
        window.clear(sf::Color::White);

        for(auto& stroke : strokes)
        {
            for(int i = 1; i < stroke.size(); i++)
            {
                sf::Vector2f p1 = stroke[i-1];
                sf::Vector2f p2 = stroke[i];

                sf::Vector2f delta = p2 - p1;

                float length = std::sqrt(delta.x*delta.x + delta.y*delta.y);
                float angleRad = std::atan2(delta.y, delta.x);

                sf::RectangleShape line(sf::Vector2f(length, thickness));
                
                line.setOrigin({0.f, thickness / 2.f});
                line.setPosition(p1);

                line.setRotation(sf::radians(angleRad));
                line.setFillColor(sf::Color::Black);

                window.draw(line);
            }
        }

        window.display();
    }
}