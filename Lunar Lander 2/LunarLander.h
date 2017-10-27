//This file is part of Lunar Lander (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include "RigidBody.h"
#include "Terrain.h" 
#include "Utility.h"

using namespace sf ;
using namespace std ;

class LunarLander : public RigidBody, public Sprite
{
public:
	LunarLander(vector<int> const& cfgData, Texture const& texture, Terrain *terrain) ;
	void updatePosition(float const& dt) ;
	void updateRotation(float const& dt) ;
	void checkCollision() ;
	void updateSound(float const& dt) ;
	void update(float const& dt) ;

	bool throttlePushed() ;
	Vector2f getThrust() ;
	Vector2f getDrag() const ;

	void updateFlame(float const& dt) ;
	ConvexShape getFlame() const ;

	float getFuel() const ;
	int getWidth() const ;
	int getHeight() const ;

	bool isAlive() const ;
	bool isWin() const ;

	void reset() ;

private :
	bool m_isAlive ;
	bool m_win ;
	float m_fuel ;
	float m_thrust ;
	float m_drag ;

	Texture m_texture ;
	int m_width ;
	int m_height ;

	ConvexShape m_flame ;
	float m_flameLength ;
	Clock m_flameTime ;

	Terrain *m_terrain ;

	int m_volume ;
	SoundBuffer m_soundBuffer ;
	Sound m_sound ;

	int m_maxAngle ;
	int m_maxDistance ;
	int m_maxSpeed ;

	int m_rotationSpeed ;

	int m_fuelBonus ;
	int m_fuelConsumption ;
};

