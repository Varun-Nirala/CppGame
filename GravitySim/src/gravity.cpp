#include <SFML/Graphics.hpp>

#include "gravity.h"
#include "object.h"

float getLength(const sf::Vector2f& v)
{
	return std::sqrtf(v.x * v.x + v.y * v.y);
}

float getLength(const sf::Vector2f &src, const sf::Vector2f &dst)
{
	return getLength(dst - src);
}

sf::Vector2f getDistance(const sf::Vector2f& src, const sf::Vector2f& dst)
{
	return (dst - src);
}

sf::Vector2f normalize(const sf::Vector2f& v, float length)
{
	return v / length;
}

sf::Vector2f normalize(const sf::Vector2f& v)
{
	return v / (getLength(v));
}

void printSfVector(const sf::Vector2f& vec)
{
	printf("%f, %f\n", vec.x, vec.y);
}

// Apply gravity to all the objects in the vector w.r.t the object at srcObjectIndex.
void Gravity::applyGravity(std::vector<Object*> vecObjects, size_t srcObjectIndex, const sf::Time& elapsedTime)
{
	if (srcObjectIndex >= vecObjects.size())
	{
		return;
	}

	// Get the srcObject.
	Object* srcObject = vecObjects[srcObjectIndex];

	// Time step in seconds
	float timeStep = elapsedTime.asSeconds();

	for (size_t i = 0; i < vecObjects.size(); ++i)
	{
		if (i != srcObjectIndex)
		{
			sf::Vector2f distanceVector = getDistance(srcObject->getPosition(), vecObjects[i]->getPosition());
			printf("distanceVector : ");
			printSfVector(distanceVector);

			// Get the distance between them.
			float magnitude = getLength(distanceVector);
			printf("magnitude : %f\n", magnitude);

			// Get the direction of the distance.
			sf::Vector2f direction = normalize(distanceVector, magnitude);
			printf("direction : ");
			printSfVector(direction);

			// Get the force of gravity.
			double force = (srcObject->getMassInKg() * vecObjects[i]->getMassInKg()) / std::powf(magnitude, 2);
			printf("Before force : %f\n", force);

			force = force * Gravity::getGravitationalConstant();
			printf("After force  : %f\n", force);

			// Get the acceleration.
			float acceleration = static_cast<float>(force) / vecObjects[i]->getMassInKg();
			printf("acceleration : %f\n", acceleration);

			if (!std::isnan(acceleration))
			{
				sf::Vector2f accelerationVector = direction * acceleration;
				printf("accelerationVector : ");
				printSfVector(accelerationVector);

				printf("Curr Velocity : ");
				printSfVector(vecObjects[i]->getVelocityInMPS());

				// Get the velocity.
				sf::Vector2f velocity = accelerationVector * timeStep;

				printf("Add Velocity  : ");
				printSfVector(velocity);

				// Update the velocity of the object.
				vecObjects[i]->setVelocityInMPS(velocity);

				srcObject->setVelocityInMPS(-velocity);
			}
		}
	}
}