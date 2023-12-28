#include <SFML/Graphics.hpp>

#include "gravity.h"
#include "object.h"

// Apply gravity to all the objects in the vector w.r.t the object at srcObjectIndex.
void Gravity::applyGravity(std::vector<Object*> vecObjects, size_t srcObjectIndex, const sf::Time& elapsedTime)
{
	if (srcObjectIndex >= vecObjects.size())
	{
		return;
	}

	// Get the object at srcObjectIndex.
	Object* srcObject = vecObjects[srcObjectIndex];

	float timeStep = elapsedTime.asSeconds() / 100.0f;

	for (size_t i = 0; i < vecObjects.size(); ++i)
	{
		if (i != srcObjectIndex)
		{
			// Get the distance between the two objects.
			sf::Vector2f distance = vecObjects[i]->getPosition() - srcObject->getPosition();

			// Get the magnitude of the distance.
			float magnitude = std::sqrtf(std::powf(distance.x, 2) + std::powf(distance.y, 2));

			// Get the direction of the distance.
			sf::Vector2f direction = distance / magnitude;

			// Get the force of gravity.
			double force = (Gravity::getGravitationalConstant() * srcObject->getMass() * vecObjects[i]->getMass()) / std::powf(magnitude, 2);

			// Get the acceleration.
			sf::Vector2f acceleration = direction * static_cast<float>(force / vecObjects[i]->getMass());

			// Get the velocity.
			sf::Vector2f velocity = acceleration * timeStep;

			// Update the velocity of the object.
			vecObjects[i]->setVelocity(velocity);
		}
	}
}