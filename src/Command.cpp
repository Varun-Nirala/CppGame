#include "Command.h"

namespace nsTetris
{
void MoveLeftCmd::execute(Actor& actor)
{
	actor.moveLeft();
}

void MoveRightCmd::execute(Actor& actor)
{
	actor.moveRight();
}

void MoveDownCmd::execute(Actor& actor)
{
	actor.moveDown();
}

void ToggleShapeCmd::execute(Actor& actor)
{
	actor.rotateCCW();
}
}