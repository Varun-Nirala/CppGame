#include "Engine\Engine.h"
#include "Graphics\Sprite.h"
#include "Engine\Common.h"
#include "Engine\IO\Mouse.h"
#include "Engine\IO\Keyboard.h"
#include "Engine\Maths\Vector3.h"
#include "Engine\Physics\RigidBody.h"

using namespace std;
using namespace nsEngine;
using namespace nsGraphics;

int main(int , char **)
{
	Engine gameEngine;
	gameEngine.Initialize("OpenGlWindow");

	std::string szCloud{ "Assets\\cloud.png" };
	nsMaths::Vector3 vecCloud{ double(gameEngine.GetWidth() - 500), double(gameEngine.GetHeight() - 200) };

	std::string szPlane{ "Assets\\Biplane.png" };
	nsMaths::Vector3 vecPlane;

	Sprite spriteCloud( szCloud, vecCloud );
	Sprite spritePlane( szPlane, vecPlane );

	spriteCloud.SetScale(nsMaths::Vector3(0.25, 0.25, 0.25));
	spritePlane.SetScale(nsMaths::Vector3(0.25, 0.25, 0.25));

	nsPhysics::RigidBody rbPlan;
	rbPlan.Initialize(&spritePlane, nsCommon::gGRAVITY, nsCommon::gFRICTION);

	/*Mouse *pMouse = Mouse::getInstance();
	if (!pMouse)
	{
		cout << __LINE__ << " ::Error: mouse instance returned NULL." << endl;
		return -1;
	}*/
	
	Keyboard *pkeyBoard = Keyboard::getInstance();
	if (!pkeyBoard)
	{
		cout << __LINE__ << " ::Error: keyboard instance returned NULL." << endl;
		return -1;
	}

	const double cFORCE = 20;

	while (!gameEngine.IsWindowClosed())
	{
		gameEngine.Update();
		spriteCloud.Update();
		spritePlane.Update();
		rbPlan.Update();

		if (pkeyBoard->Key(GLFW_KEY_W))			// Up
		{
			spritePlane.IncrementRotation(1);
			rbPlan.AddForce(nsMaths::Vector3(0, cFORCE, 0));
		}
		else if (pkeyBoard->Key(GLFW_KEY_S))	// Down
		{
			spritePlane.IncrementRotation(-1);
			rbPlan.AddForce(nsMaths::Vector3(0, -cFORCE, 0));
		}
		else if (pkeyBoard->Key(GLFW_KEY_A))	// Left
		{
			rbPlan.AddForce(nsMaths::Vector3(-cFORCE*10, 0, 0));
		}
		else if (pkeyBoard->Key(GLFW_KEY_D))	// Right
		{
			rbPlan.AddForce(nsMaths::Vector3(cFORCE*10, 0, 0));
		}

		gameEngine.BeginRender();
		spriteCloud.Render();
		spritePlane.Render();
		rbPlan.Render(nsMaths::Vector3(0, 0, 0));
		gameEngine.EndRender();
	}

	return 0;
}