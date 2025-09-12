#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "brush.hpp"

int main()
{
    sf::RenderWindow window;

    window.create(sf::VideoMode({800, 600}), "Paint", sf::Style::Default);

    sf::View drawingView(sf::FloatRect({0.f, 0.f}, {(float)window.getSize().x, (float)window.getSize().y}));
    window.setView(drawingView);

    sf::Clock clock;

    Brush brush;

    std::vector<sf::Vector2f> currentStroke;
    sf::Color currentColor = sf::Color::Black;

    float thickness = 5.f;

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
                    brush.pushStroke(currentStroke, currentColor);
                    currentStroke.clear();
                }
            }

            if(event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Num1)
            {
                currentColor = sf::Color::Red;
                brush.setColor(currentColor);
            }
        }

        // Update
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
            
            if(currentStroke.empty() || currentStroke.back() != worldPos)
                currentStroke.push_back(worldPos);
        }
    
        // Draw
        window.clear(sf::Color::White);

        brush.drawStroke(window);

        brush.drawStrokeLive(window, currentStroke, currentColor);
        
        window.display();
    }
}