#include "RigidBody.h"
#include "..\Common.h"

using namespace nsEngine;
using namespace nsEngine::nsPhysics;
using namespace nsEngine::nsMaths;

RigidBody::RigidBody()
	: m_pSprite(NULL)
	, m_Gravity(nsCommon::gGRAVITY)
	, m_Vec3Friction(nsCommon::gFRICTION)
{}

RigidBody::~RigidBody()
{}

void RigidBody::Initialize(nsGraphics::Sprite *sprite, double gravity, const Vector3 &friction)
{
	m_pSprite = sprite;
	m_Gravity = gravity;
	m_Vec3Friction = friction;
}

void RigidBody::AddForce(const Vector3 &force)
{
	m_pSprite->IncrementVelocity(force);
}

void RigidBody::Update()
{
	Vector3 &vel = m_pSprite->GetVelocity();

	// Apply friction and gravity
	vel *= m_Vec3Friction;		// friction on All direction
	vel.m_y += m_Gravity;		// gravity only in down direction

	Vector3 &pos = m_pSprite->GetPosition();
	pos += vel;
}

void RigidBody::Render(const Vector3 &vec3Color)
{
	glLoadIdentity();

	Vector3 &pos = m_pSprite->GetPosition();
	Vector3 &scale = m_pSprite->GetScale();
	Vector3 &rot = m_pSprite->GetRotation();
	const Vector3 &size = m_pSprite->GetSize();

	// Transate, Rotate, Scale
	glTranslatef((GLfloat)pos.m_x, (GLfloat)pos.m_y, (GLfloat)pos.m_z);
	glScalef((GLfloat)scale.m_x, (GLfloat)scale.m_y, (GLfloat)scale.m_z);
	glRotatef((GLfloat)rot.m_x, (GLfloat)rot.m_y, (GLfloat)rot.m_z, 1);

	glColor4f((GLfloat)vec3Color.m_x, (GLfloat)vec3Color.m_y, (GLfloat)vec3Color.m_z, 1);

	glBegin(GL_LINES);
	{
		glVertex2i(0, 0);
		glVertex2i((int)size.m_x, 0);

		glVertex2i((int)size.m_x, 0);
		glVertex2i((int)size.m_x, (int)size.m_y);

		glVertex2i((int)size.m_x, (int)size.m_y);
		glVertex2i(0, (int)size.m_y);

		glVertex2i(0, (int)size.m_y);
		glVertex2i(0, 0);
	}
	glEnd();
}