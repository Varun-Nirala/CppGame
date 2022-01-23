#include "Sprite.h"
#include "..\Engine\Common.h"

using namespace nsEngine;
using namespace nsEngine::nsMaths;
using namespace nsGraphics;
using namespace std;

Sprite::Sprite()
	: m_Vec3Color(1, 1, 1)
	, m_Force(1.0)
{}

Sprite::Sprite(string &path)
	:Sprite()
{
	m_Texture = Texture(path);
	m_Vec3Size.m_x = m_Texture.GetWidth();
	m_Vec3Size.m_y = m_Texture.GetHeight();
	m_Vec3Size.m_z = 1;
}

Sprite::Sprite(string &path, double x, double y, double z)
	: Sprite(path)
{
	m_Vec3Pos = Vector3(x, y, z);
}

Sprite::Sprite(string &path, const Vector3 &VecPos)
	: Sprite(path)
{
	m_Vec3Pos = VecPos;
}

Vector3& Sprite::GetPosition()
{
	return m_Vec3Pos;
}

Vector3& Sprite::GetScale()
{
	return m_Vec3Scale;
}

Vector3& Sprite::GetRotation()
{
	return m_Vec3Rotation;
}

Vector3& Sprite::GetVelocity()
{
	return m_Vec3Vel;
}

const Vector3 Sprite::GetSize() const
{
	return m_Vec3Size;
}

void Sprite::SetPosition(const Vector3 &vec)
{
	m_Vec3Pos = vec;
}

void Sprite::IncrementPosition(const Vector3 &vec)
{
	m_Vec3Pos += (vec * nsCommon::getElapsedTime());
}

void Sprite::SetRotation(const Vector3 &vec)
{
	m_Vec3Rotation = vec;
}

void Sprite::IncrementRotation(const Vector3 &vec)
{
	m_Vec3Rotation += (vec * nsCommon::getElapsedTime());
}

void Sprite::SetScale(const Vector3 &vec)
{
	m_Vec3Scale = vec;
}

void Sprite::SetVelocity(const Vector3 &vec)
{
	cout << "Setting Velocity : " << vec << endl;
	m_Vec3Vel = vec;
}

void Sprite::IncrementVelocity(const Vector3 &vec)
{
	cout << "Incrementing Velocity By : " << vec << endl;
	
	m_Vec3Vel += (vec * nsCommon::getElapsedTime());

	cout << "New Velocity By : " << m_Vec3Pos << endl;
}

void Sprite::Update()
{
	m_Vec3Pos += m_Vec3Vel;
	cout << "In Update Velocity is : " << m_Vec3Pos << endl;
}

void Sprite::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Texture.GetID());
	glLoadIdentity();

	// Transate, Rotate, Scale
	glTranslatef((GLfloat)m_Vec3Pos.m_x, (GLfloat)m_Vec3Pos.m_y, (GLfloat)m_Vec3Pos.m_z);
	glScalef((GLfloat)m_Vec3Scale.m_x, (GLfloat)m_Vec3Scale.m_y, (GLfloat)m_Vec3Scale.m_z);
	glRotatef((GLfloat)m_Vec3Rotation.m_x, (GLfloat)m_Vec3Rotation.m_y, (GLfloat)m_Vec3Rotation.m_y, 1);

	//Rendering
	glColor4f((GLfloat)m_Vec3Color.m_x, (GLfloat)m_Vec3Color.m_y, (GLfloat)m_Vec3Color.m_z, 1);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);

		glTexCoord2f(1, 0);
		glVertex2f((GLfloat)m_Texture.GetWidth(), 0);

		glTexCoord2f(1, 1);
		glVertex2f((GLfloat)m_Texture.GetWidth(), (GLfloat)m_Texture.GetHeight());

		glTexCoord2f(0, 1);
		glVertex2f(0, (GLfloat)m_Texture.GetHeight());
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}