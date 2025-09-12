#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Brush
{
    private:
        float m_thickness;
        sf::Color m_color;
        std::vector<std::pair<std::vector<sf::Vector2f>, sf::Color>> m_strokes;
    public:
        Brush() : m_thickness(5.f), m_color(sf::Color::Black) {}

        void setThickness(float t);
        void setColor(const sf::Color& c);

        void pushStroke(const std::vector<sf::Vector2f>& stroke, const sf::Color& color);

        void drawStroke(sf::RenderWindow& window);
        void drawStrokeLive(sf::RenderWindow& window, const std::vector<sf::Vector2f>& currentStroke, const sf::Color& color);
};