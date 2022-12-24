#pragma once

#include "components.h"

class FontRenderer : public Components
{
public:
	void start() override;
	void update(GLfloat dt) override;

private:
};

void FontRenderer::start()
{

}

void FontRenderer::update(GLfloat dt)
{
	(void)dt;
}