#include "BattleShip.h"

using namespace AsteroidNS;

float const BattleShip::m_kBulletDelay{ 0.25f };

BattleShip::~BattleShip()
{
    ;
}

BattleShip::BattleShip(const sf::Vector2f& headPos, float size)
    : m_rect(sf::Vector2f(size, size))
{
    //m_rect.setOrigin(size / 2.0f, size / 2.0f);

    m_texture.loadFromFile(R"(./resources/Jet.png)");
    m_rect.setTexture(&m_texture, true);

    m_rect.setPosition(headPos);

    m_front.x = m_rect.getPosition().x + getSize() / 2.0f;
    m_front.y = m_rect.getPosition().y;
}

sf::Vector2f BattleShip::getFront() const
{
    return m_front;
}

sf::Vector2f BattleShip::getOrigin() const
{
    return m_rect.getOrigin();
}

void BattleShip::setCanFire(bool val)
{
    m_bCanFire = val;
}

bool BattleShip::canFire()
{
    return m_bCanFire && m_lastFire >= m_kBulletDelay;
}

float AsteroidNS::BattleShip::getSize()
{
    return m_rect.getSize().x;
}

Bullet* BattleShip::fire()
{
    m_lastFire = 0.0f;
    Bullet* b = new Bullet();

    b->setPosition(m_front);
    
    b->setDirection(m_forwardDirection);
    return b;
}

void BattleShip::update(float secElapsed)
{
    m_lastFire += secElapsed;
    m_front.x = m_rect.getPosition().x + getSize() / 2.0f;
    m_front.y = m_rect.getPosition().y;

    m_rect.setRotation(m_rollAngleInDeg);
    m_rollAngleInDeg = 0.0f;
}

void BattleShip::render(sf::RenderWindow& w) const
{
    w.draw(m_rect);
}