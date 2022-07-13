#include "BattleShip.h"

using namespace AsteroidNS;

FighterJet::FighterJet(BattleShip* pBoundTo, const std::string& image, float w, float h)
{
    m_boundedTo = pBoundTo;
    init(image, (int)w, (int)h);
}

void FighterJet::update(float secElapsed)
{
    (void)secElapsed;
    m_sprite.setPosition(m_boundedTo->getHeadPosition() - sf::Vector2f(m_boundedTo->getSize() / 2.0f, 0.0f));
}

void FighterJet::render(sf::RenderWindow& w) const
{
    w.draw(m_sprite);
}

bool FighterJet::init(const std::string& imagePath, int w, int h)
{
    if (!m_texture.loadFromFile(imagePath, sf::IntRect(0, 0, w, h)))
    {
        return false;
    }
    m_sprite.setTexture(m_texture);
    return true;
}

float const BattleShip::m_kBulletDelay{ 0.5f };

BattleShip::BattleShip(const sf::Vector2f& headPos, float size)
    :m_triangle(sf::Triangles, 3)
    , m_originPos(headPos)
    , m_size(size)
    , m_jet(this, R"(./resources/Jet.png)", size, size)
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

float AsteroidNS::BattleShip::getSize()
{
    return m_size;
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
    adjustPos();
    m_jet.update(secElapsed);
}

void BattleShip::render(sf::RenderWindow& w) const
{
    w.draw(m_triangle);
    m_jet.render(w);
}

void BattleShip::adjustPos()
{
    m_triangle[HEAD].position.x = m_originPos.x;
    m_triangle[HEAD].position.y = m_originPos.y;

    m_triangle[LEFT].position.x = m_originPos.x - (m_size / 2.0f);
    m_triangle[LEFT].position.y = m_originPos.y + (m_size * 0.866f);        // sqrt(3) / 2

    m_triangle[RIGHT].position.x = m_originPos.x + (m_size / 2.0f);
    m_triangle[RIGHT].position.y = m_originPos.y + (m_size * 0.866f);
}