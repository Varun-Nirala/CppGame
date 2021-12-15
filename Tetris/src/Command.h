#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "TetrisShapes.h"

namespace nsTetris
{
using Actor = TetrisShape;

class Command
{
public:
	virtual void execute(Actor &actor) = 0;
};

class MoveLeftCmd : public Command
{
public:
	virtual void execute(Actor& actor);
};

class MoveRightCmd : public Command
{
public:
	virtual void execute(Actor& actor);
};

class MoveDownCmd : public Command
{
public:
	virtual void execute(Actor& actor);
};

class ToggleShapeCmd : public Command
{
public:
	virtual void execute(Actor& actor);
};
}
#endif // #ifndef __COMMAND_H__