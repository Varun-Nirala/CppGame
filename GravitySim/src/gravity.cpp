#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#include "gravity.h"
#include "object.h"
#include "logger.h"
#include "helper.h"

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

			Helper::printVector("\n\nDistanceVector: ", distanceVector);
			Helper::printVector(", DirectionVector: ", direction);
			

			ns_Util::Logger::LOG_MSG(", Mag: ", magnitude, "Val: ", Gravity::getGravitationalConstant() * srcObject->getMass() * vecObjects[i]->getMass(), '\n');

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