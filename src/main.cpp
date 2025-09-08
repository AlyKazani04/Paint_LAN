#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>



int main()
{
    sf::RenderWindow window;

    window.create(sf::VideoMode({800, 600}), "Paint", sf::Style::Default);

    sf::View view = window.getView();

    sf::Clock clock;

    while(window.isOpen())
    {
        while(const std::optional<sf::Event> event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // Update
        {
    
        }
    
        // Draw
        {
            window.clear(sf::Color::White);
            
            window.display();
        }
    }
}