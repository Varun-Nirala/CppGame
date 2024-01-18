#ifndef __GRAVITY_H__
#define __GRAVITY_H__

#include <vector>

class sf::Time;
class Object;

class Gravity
{
public:
	// Apply gravity to all the objects in the vector w.r.t the object at srcObjectIndex.
	static void applyGravity(std::vector<Object *> vecObjects, size_t srcObjectIndex);

	static double getGravitationalConstant() { return m_gravitationalConstant; }

private:

	static constexpr double m_gravitationalConstant = 6.673e-11;
};

#endif