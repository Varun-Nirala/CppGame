#ifndef __BATTLESHIP_H__
#define __BATTLESHIP_H__

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Bullet.h"

namespace AsteroidNS
{
    class FighterJet
    {
    public:
        FighterJet(const std::string& image)
        {
            init(image);
        }

        void update(float secElapsed)
        {
            (void)secElapsed;
        }

        void render(sf::RenderWindow& w) const
        {
            w.draw(m_sprite);
        }

    private:
        bool init(const std::string& imagePath)
        {
            sf::Image image;
            if (!image.loadFromFile(imagePath))
            {
                return false;
            }
            if (!m_texture.loadFromImage(image))
            {
                return false;
            }
            m_sprite.setTexture(m_texture);
            return true;
        }
    private:
        sf::Texture     m_texture;
        sf::Sprite      m_sprite;
    };

    class BattleShip
    {
        enum Orient
        {
            LEFT,
            HEAD,
            RIGHT,
        };

    public:
        BattleShip(const sf::Vector2f& headPos = { 0, 0 }, int size = 50)
            :m_triangle(sf::Triangles, 3)
            , m_originPos(headPos)
            , m_size(size)
            , m_jet(R"(./resources/Jet.png)")
        {
            adjustPos();    // always call after changing head as it orient according to head

            m_triangle[HEAD].color = sf::Color::Blue;
            m_triangle[LEFT].color = m_triangle[RIGHT].color = sf::Color::Red;
        }

        sf::Vector2f getHeadPosition() const
        {
            return m_triangle[HEAD].position;
        }

        void setOrigin(const sf::Vector2f& head)
        {
            m_originPos = head;
        }

        bool canFire()
        {
            return true;
        }

        Bullet* fire() const
        {
            Bullet* b = new Bullet();
            b->setPosition(m_triangle[HEAD].position);
            b->setDirection(m_forwardDirection);
            return b;
        }

        void update(float secElapsed)
        {
            (void)secElapsed;
            adjustPos();
        }

        void render(sf::RenderWindow& w) const
        {
            w.draw(m_triangle);
            m_jet.render(w);
        }

    private:
        void adjustPos()
        {
            m_triangle[HEAD].position.x = m_originPos.x;
            m_triangle[HEAD].position.y = m_originPos.y - m_size;

            m_triangle[LEFT].position.x = m_originPos.x - m_size;
            m_triangle[LEFT].position.y = m_originPos.y + m_size;

            m_triangle[RIGHT].position.x = m_originPos.x + m_size;
            m_triangle[RIGHT].position.y = m_originPos.y + m_size;
        }

    private:
        sf::VertexArray     m_triangle{};
        sf::Vector2f        m_originPos{};
        sf::Vector2f        m_forwardDirection{0.0f, -1.0f};
        int                 m_size{};
        float               m_lastFire;
        static const float  m_kBulletDelay;
        FighterJet          m_jet;
};

float const BattleShip::m_kBulletDelay{ 0.5f };
}

#endif //__BATTLESHIP_H__