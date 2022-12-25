#ifndef __RAYCASTING_H__
#define __RAYCASTING_H__

#include "common/logger.h"
#include "common/constants.h"
#include "common/common.h"

#include "objectRenderer.h"

#include <vector>

class Game;

class Raycasting
{
public:
	explicit Raycasting(Game* pGame);

	void raycast();

	void update(float dt);
	void draw();

	const std::vector<TextureObject>& getObjectsToRender() const { return m_objectsToRender; }
	std::vector<TextureObject>& getObjectsToRender() { return m_objectsToRender; }

private:
	void fillObjectsToRender();

	void drawRays();
	void drawWalls();

private:
	Game							*m_pGame{};
	std::vector<Line>				m_rays;
	std::vector<Rectangle>			m_rectangles;
	std::vector<RaycastingResult>	m_results;

	std::vector<TextureObject>		m_objectsToRender;
};

#endif //!__RAYCASTING_H__