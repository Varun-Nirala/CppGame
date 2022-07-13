#ifndef __BATTLESHIP_H__
#define __BATTLESHIP_H__

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Bullet.h"

namespace AsteroidNS
{

class BattleShip;
class FighterJet
{
public:
    FighterJet(BattleShip *pBoundTo, const std::string& image, float w, float h);

    void update(float secElapsed);
    void render(sf::RenderWindow& w) const;

private:
    bool init(const std::string& imagePath, int w, int h);
private:
    sf::Texture     m_texture;
    sf::Sprite      m_sprite;
    BattleShip      *m_boundedTo{};
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
    BattleShip(const sf::Vector2f& headPos = { 0, 0 }, float size = 100.0f);

    sf::Vector2f getHeadPosition() const;

    void setOrigin(const sf::Vector2f& head);

    void setCanFire(bool val);
    bool canFire();

    float getSize();

    Bullet* fire() const;

    void update(float secElapsed);

    void render(sf::RenderWindow& w) const;

private:
    void adjustPos();

private:
    sf::VertexArray     m_triangle{};
    sf::Vector2f        m_originPos{};
    sf::Vector2f        m_forwardDirection{0.0f, -1.0f};
    FighterJet          m_jet;
    bool                m_bCanFire{ false };
    float               m_size{};
    float               m_lastFire;

    static const float  m_kBulletDelay;
};
}
#endif //__BATTLESHIP_H__