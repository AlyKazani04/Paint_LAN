#include "brush.hpp"

void Brush::setThickness(float t)
{
    m_thickness = t;
}

void Brush::setColor(const sf::Color& c)
{
    m_color = c;
}

void Brush::pushStroke(const std::vector<sf::Vector2f>& stroke, const sf::Color& color)
{
    m_strokes.push_back({stroke, color});
}

void Brush::drawStroke(sf::RenderWindow& window)
{
    for(auto& stroke : m_strokes)
    {

        drawStrokeLive(window, stroke.first, stroke.second);
    }
}

void Brush::drawStrokeLive(sf::RenderWindow& window, const std::vector<sf::Vector2f>& currentStroke, const sf::Color& color)
{
    if (currentStroke.empty())
            return;
    
        if (currentStroke.size() == 1) {
            sf::RectangleShape point({m_thickness, m_thickness});
            point.setOrigin({m_thickness / 2.f, m_thickness / 2.f});
            point.setPosition(currentStroke[0]);
            point.setFillColor(m_color);
            window.draw(point);
            return;
        }
    
        for (int i = 1; i < currentStroke.size(); i++) {
            sf::Vector2f p1 = currentStroke[i - 1];
            sf::Vector2f p2 = currentStroke[i];
            sf::Vector2f delta = p2 - p1;
    
            float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);
            float angleRad = std::atan2(delta.y, delta.x);
    
            sf::RectangleShape line(sf::Vector2f(length, m_thickness));
            line.setOrigin({0.f, m_thickness / 2.f});
            line.setPosition(p1);
            line.setRotation(sf::radians(angleRad));
            line.setFillColor(color);
    
            window.draw(line);
        }
}