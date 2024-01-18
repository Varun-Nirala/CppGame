#include <SFML/Graphics.hpp>

#include "gravity.h"
#include "object.h"
#include "logger.h"
#include "helper.h"

float getMagnitude(const sf::Vector2f& v)
{
	return std::sqrtf(std::powf(v.x, 2) + std::powf(v.y, 2));
}

float getMagnitude(const sf::Vector2f &src, const sf::Vector2f &dst)
{
	return getMagnitude(src - dst);
}

sf::Vector2f getDistance(const sf::Vector2f& src, const sf::Vector2f& dst)
{
	return (src - dst);
}

sf::Vector2f normalize(const sf::Vector2f& v, float magnitude)
{
	return v / magnitude;
}

sf::Vector2f normalize(const sf::Vector2f& v)
{
	return normalize(v, getMagnitude(v));
}

// Apply gravity to all the objects in the vector w.r.t the object at srcObjectIndex.
void Gravity::applyGravity(std::vector<Object*> vecObjects, size_t srcObjectIndex)
{
	if (srcObjectIndex >= vecObjects.size())
	{
		return;
	}
		
	// Get the srcObject.
	const Object* srcObject = vecObjects[srcObjectIndex];

	for (size_t i = 0; i < vecObjects.size(); ++i)
	{
		if (i != srcObjectIndex)
		{
			const sf::Vector2f distanceVector = getDistance(srcObject->getPosition(), vecObjects[i]->getPosition());
			
			const float magnitude = getMagnitude(distanceVector);

			// Get the direction of the distance.
			sf::Vector2f direction = normalize(distanceVector, magnitude);
			Helper::printSfVector("DistanceVector: ", distanceVector);
			Helper::printSfVector(", DirectionVector: ", direction);
			ns_Util::Logger::LOG_MSG(", Mag: ", magnitude, '\n');

			// Get the force of gravity.
			const float force = static_cast<float>(Gravity::getGravitationalConstant() * srcObject->getMass() * vecObjects[i]->getMass()) / std::powf(magnitude, 2);
			
			const float theta = std::atan2f(distanceVector.y, distanceVector.x);

			sf::Vector2f forceVector;
			forceVector.x = std::cosf(theta) * force;
			forceVector.y = std::sinf(theta) * force;

			Helper::printSfVector("ForceVector: ", forceVector);
			ns_Util::Logger::LOG_MSG(", Force: ", force, '\n');
			vecObjects[i]->addForce(forceVector);
		}
	}
}