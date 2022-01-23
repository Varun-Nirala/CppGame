#ifndef __RIGID_BODY_H__
#define __RIGID_BODY_H__

#include "..\Maths\Vector3.h"
#include "..\..\Graphics\Sprite.h"

namespace nsEngine { namespace nsPhysics
{
	class RigidBody
	{
		public:
			RigidBody();
			~RigidBody();

			void Initialize(nsGraphics::Sprite *sprite,
				const double gravity,
				const nsEngine::nsMaths::Vector3 &friction);

			void Update();
			void Render(const nsEngine::nsMaths::Vector3 &color);

			void AddForce(const nsEngine::nsMaths::Vector3 &force);

		private:
			nsGraphics::Sprite			*m_pSprite;

			double						m_Gravity;
			nsEngine::nsMaths::Vector3	m_Vec3Friction;
	};
}}
#endif