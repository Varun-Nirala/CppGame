#include "BattleShip.h"

using namespace AsteroidNS;

FighterJet::FighterJet(const std::string& image)
{
    init(image);
}

void FighterJet::update(float secElapsed)
{
    (void)secElapsed;
}

void FighterJet::render(sf::RenderWindow& w) const
{
    w.draw(m_sprite);
}

bool FighterJet::init(const std::string& imagePath)
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

float const BattleShip::m_kBulletDelay{ 0.5f };

BattleShip::BattleShip(const sf::Vector2f& headPos, int size)
    :m_triangle(sf::Triangles, 3)
    , m_originPos(headPos)
    , m_size(size)
    , m_jet(R"(./resources/Jet.png)")
{
    adjustPos();    // always call after changing head as it orient according to head

    m_triangle[HEAD].color = sf::Color::Blue;
    m_triangle[LEFT].color = m_triangle[RIGHT].color = sf::Color::Red;
}

sf::Vector2f BattleShip::getHeadPosition() const
{
    return m_triangle[HEAD].position;
}

void BattleShip::setOrigin(const sf::Vector2f& head)
{
    m_originPos = head;
}

void BattleShip::setCanFire(bool val)
{
    m_bCanFire = val;
}

bool BattleShip::canFire()
{
    return m_bCanFire;
}

Bullet* BattleShip::fire() const
{
    Bullet* b = new Bullet();
    b->setPosition(m_triangle[HEAD].position);
    b->setDirection(m_forwardDirection);
    return b;
}

void BattleShip::update(float secElapsed)
{
    (void)secElapsed;
    adjustPos();
}

void BattleShip::render(sf::RenderWindow& w) const
{
    w.draw(m_triangle);
    m_jet.render(w);
}

void BattleShip::adjustPos()
{
    m_triangle[HEAD].position.x = m_originPos.x;
    m_triangle[HEAD].position.y = m_originPos.y - m_size;

    m_triangle[LEFT].position.x = m_originPos.x - m_size;
    m_triangle[LEFT].position.y = m_originPos.y + m_size;

    m_triangle[RIGHT].position.x = m_originPos.x + m_size;
    m_triangle[RIGHT].position.y = m_originPos.y + m_size;
}