//This file is part of Lunar Lander (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "RigidBody.h"

RigidBody::RigidBody()
{
	m_mass = 50 ;
	m_position = Vector2f(50,50) ;
	m_speed = Vector2f(0,0) ;
	m_acceleration = Vector2f(0,0) ;
	m_movable = true ;
}
RigidBody::RigidBody(float mass, Vector2f position, Vector2f speed)
{
	m_mass = mass ;
	m_position = position ;
	m_speed = speed ;
}

float RigidBody::getMass() const
{
	return m_mass ;
}
void RigidBody::setMass(float const& mass)
{
	m_mass=mass ;
}

vector<Vector2f> RigidBody::getForce() const
{
	return m_force ;
}
Vector2f RigidBody::getTotalForce() const
{
	Vector2f totalForce(0,0) ;
	for(int i(0) ; i < m_force.size() ; i++)
	{
		totalForce += m_force[i] ;
	}
	return totalForce ;
}
void RigidBody::addForce(Vector2f const& force)
{
	m_force.push_back(force) ;
}
void RigidBody::clearForce()
{
	m_force.clear() ;
}

Vector2f RigidBody::RBgetPosition() const
{
	return m_position ;
}
Vector2f RigidBody::getPreviousPosition() const
{
	return m_previousPosition ;
}
void RigidBody::RBsetPosition(Vector2f const& position)
{
	m_position = position ;
}

Vector2f RigidBody::getSpeed() const
{
	return m_speed ;
}
void RigidBody::setSpeed(Vector2f const& speed)
{
	m_speed = speed ;
}

Vector2f RigidBody::getAcceleration() const
{
	return m_acceleration ;
}
void RigidBody::setAcceleration(Vector2f const& acceleration)
{
	m_acceleration = acceleration ;
}
void RigidBody::setStatic()
{
	m_movable = false ;
}
void RigidBody::setMovable()
{
	m_movable = true ;
}
bool RigidBody::isMovable()
{
	return m_movable ;
}

void RigidBody::RBupdatePosition(float const& dt)
{
	m_previousPosition = m_position ;
	m_position = m_position + m_speed*dt + 0.5f*getTotalForce()/m_mass*(float)pow(dt,2);
	m_speed = (m_position-m_previousPosition)/dt ;
}