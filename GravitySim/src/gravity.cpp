#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

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
			const glm::dvec2 distanceVector = srcObject->getPosition() - vecObjects[i]->getPosition();
			
			const double magnitude = glm::length(distanceVector);

			const glm::dvec2 direction = glm::normalize(distanceVector);

			Helper::printVector("DistanceVector: ", distanceVector);
			Helper::printVector(", DirectionVector: ", direction);
			ns_Util::Logger::LOG_MSG(", Mag: ", magnitude, '\n');

			// Get the force of gravity.
			const double force = Gravity::getGravitationalConstant() * srcObject->getMass() * vecObjects[i]->getMass() / std::pow(magnitude, 2);
			
			const double theta = std::atan2(distanceVector.y, distanceVector.x);

			glm::dvec2 forceVector(std::cos(theta) * force, std::sin(theta) * force);

			Helper::printVector("ForceVector: ", forceVector);
			ns_Util::Logger::LOG_MSG(", Force: ", force, "\n\n");
			vecObjects[i]->addForce(forceVector);
		}
	}
}