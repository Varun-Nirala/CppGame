#ifndef __BATTLESHIP_H__
#define __BATTLESHIP_H__

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Bullet.h"

namespace AsteroidNS
{
class BattleShip
{
    enum Orient
    {
        LEFT,
        HEAD,
        RIGHT,
    };

public:
    ~BattleShip();
    BattleShip(const sf::Vector2f& headPos = { 0, 0 }, float size = 100.0f);

    void move(const sf::Vector2f& offset) { m_rect.move(offset); }
    void move(float x, float y) { m_rect.move(x, y); }
    sf::Vector2f getPosition() const { return m_rect.getPosition(); }

    sf::Vector2f getFront() const;
    sf::Vector2f getOrigin() const;

    void setCanFire(bool val);
    bool canFire();

    float getSize();

    void setRoll(float val) { m_rollAngleInDeg = val; }

    float setRoll() const { return m_rollAngleInDeg; }

    Bullet* fire();

    void update(float secElapsed);

    void render(sf::RenderWindow& w) const;

private:
    sf::RectangleShape  m_rect;
    sf::Texture         m_texture;
    sf::Vector2f        m_front{};
    sf::Vector2f        m_forwardDirection{0.0f, -1.0f};
    bool                m_bCanFire{ false };
    float               m_lastFire{};

    float               m_rollAngleInDeg{};

    static const float  m_kBulletDelay;
};
}
#endif //__BATTLESHIP_H__