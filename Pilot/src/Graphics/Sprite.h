#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Texture.h"
#include "..\Engine\Maths\Vector3.h"
#include <iostream>

namespace nsGraphics
{
	class Sprite
	{
		public:
			Sprite();
			Sprite(std::string &path);
			Sprite(std::string &path, double x, double y, double z = 1);
			Sprite(std::string &path, const nsEngine::nsMaths::Vector3 &VecPos);

			void Update();
			void Render();

			// Getters
			nsEngine::nsMaths::Vector3& GetPosition();
			nsEngine::nsMaths::Vector3& GetScale();
			nsEngine::nsMaths::Vector3& GetRotation();
			nsEngine::nsMaths::Vector3& GetVelocity();

			const nsEngine::nsMaths::Vector3  GetSize() const;

			// TRANSLATE
			void SetPosition(const nsEngine::nsMaths::Vector3 &);
			void IncrementPosition(const nsEngine::nsMaths::Vector3 &);

			// ROTATE
			void SetRotation(const nsEngine::nsMaths::Vector3 &);
			void IncrementRotation(const nsEngine::nsMaths::Vector3 &);

			// SCALE
			void SetScale(const nsEngine::nsMaths::Vector3 &);

			// SPEED
			void SetVelocity(const nsEngine::nsMaths::Vector3 &vec);
			void IncrementVelocity(const nsEngine::nsMaths::Vector3 &vec);

			// Force

		private:
			Texture						m_Texture;

			// COLOR
			nsEngine::nsMaths::Vector3	m_Vec3Color;

			// TRANSLATE
			nsEngine::nsMaths::Vector3	m_Vec3Pos;

			// ROTATE
			nsEngine::nsMaths::Vector3	m_Vec3Rotation;

			// SCALE
			nsEngine::nsMaths::Vector3	m_Vec3Scale;

			// SPEED
			nsEngine::nsMaths::Vector3	m_Vec3Vel;

			// FORCE
			double						m_Force;

			// SIZE
			nsEngine::nsMaths::Vector3	m_Vec3Size;
	};
}
#endif