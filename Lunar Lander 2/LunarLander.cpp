//This file is part of Lunar Lander (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "LunarLander.h"

LunarLander::LunarLander(vector<int> const& cfgData, Texture const& texture, Terrain *terrain)
{
	RBsetPosition(Vector2f(0,0)) ;
	Sprite::setPosition(Vector2f(0,0)) ;
	setMass(cfgData[6]) ;
	setMovable() ;

	m_thrust = cfgData[7] ;
	m_drag = cfgData[8] ;
	m_fuel = cfgData[9] ;

	m_texture = texture ;
	setTexture(m_texture) ;
	m_width = m_texture.getSize().x ; m_height = m_texture.getSize().y ;
	setOrigin(m_width/2.f,m_height/2.f) ;
	m_texture.setSmooth(true) ;

	m_flame.setPointCount(3) ;
	m_flame.setPoint(0,Vector2f(-5,0));
	m_flame.setPoint(1,Vector2f(5,0));
	m_flame.setPoint(2,Vector2f(0,0));
	m_flame.setFillColor(Color::Transparent) ;
	m_flame.setOutlineThickness(1);
	
	m_flame.setOrigin(getOrigin() - Vector2f( m_texture.getSize().x/2, m_texture.getSize().x/1.4));
	m_flame.setPosition(getPosition()) ;
	m_flameLength = 0 ;

	m_terrain = terrain ;

	m_isAlive = true ;
	m_win = false ;

	m_soundBuffer.loadFromFile("Ressources/burner.aif") ;
	m_sound.setBuffer(m_soundBuffer) ;
	m_sound.setLoop(true) ;
	m_sound.play() ;
	m_sound.setVolume(0) ;

	m_maxAngle = cfgData[11] ;
	m_maxDistance = cfgData[12] ;
	m_maxSpeed = cfgData[13] ;

	m_rotationSpeed = cfgData[14] ;

	m_fuelBonus = cfgData[15] ;
	m_fuelConsumption = cfgData[16] ;

	m_volume = cfgData[17] ;
}
void LunarLander::updatePosition(float const& dt)
{
	RBupdatePosition(dt) ;
	Sprite::setPosition(RBgetPosition()) ;
}
void LunarLander::updateRotation(float const& dt)
{
	if(Keyboard::isKeyPressed(Keyboard::Left))
		Sprite::rotate(-m_rotationSpeed*dt) ;
	if(Keyboard::isKeyPressed(Keyboard::Right))
		Sprite::rotate(m_rotationSpeed*dt) ;
}
void LunarLander::checkCollision()
{
	Vector2f TL = rotatePoint( getPosition()+Vector2f(-m_width/3.2f,-m_height/2.f), getPosition(), getRotation()) ;
	Vector2f TR = rotatePoint( getPosition()+Vector2f(+m_width/3.2f,-m_height/2.f), getPosition(), getRotation()) ;
	Vector2f BL = rotatePoint( getPosition()+Vector2f(-m_width/2.f,+m_height/2.f), getPosition(), getRotation()) ;
	Vector2f BR = rotatePoint( getPosition()+Vector2f(+m_width/2.f,+m_height/2.f), getPosition(), getRotation()) ;

	for(int i( (int)( minClamp((getPosition().x-m_terrain->getCenterPosition().x-m_width/2.f)/(float)m_terrain->getVertexSpacing() ,0))) ; 
			i <(int)( maxClamp((getPosition().x-m_terrain->getCenterPosition().x+m_width/2.f)/(float)m_terrain->getVertexSpacing() , m_terrain->getSize()-1)) ; i++)
	{
		if(collisionTrianglePoint(TL, TR, BL, m_terrain->getPoint(i)) || collisionTrianglePoint(TR, BR, BL, m_terrain->getPoint(i))) 
		{
			m_isAlive = false ;
			float distance = 0 ;

			for(int i( (int)( minClamp((getPosition().x-m_terrain->getCenterPosition().x-m_width/2.f)/(float)m_terrain->getVertexSpacing() ,0))) ; 
			i <(int)( maxClamp((getPosition().x-m_terrain->getCenterPosition().x+m_width/2.f)/(float)m_terrain->getVertexSpacing() , m_terrain->getSize()-1)) ; i++)
			{
				distance += m_terrain->getPoint(i).y - (BL.y+BR.y)/2.f ;
			} distance = abs(distance) ;
			if(distance < m_maxDistance && Norm(getSpeed()) < m_maxSpeed && (getRotation() < m_maxAngle || getRotation() > 360-m_maxAngle))
			{
				m_win = true ;
				m_fuel += m_fuelBonus ;
			}
			else
			{
				m_win = false ;
				m_fuel -= m_fuelBonus ;
			}
			
			return ;
		}
	}
}
void LunarLander::updateSound(float const& dt)
{
	if(throttlePushed() && isAlive()) m_sound.setVolume(maxClamp(m_sound.getVolume() + 200*dt,m_volume)) ;
	else m_sound.setVolume(minClamp(m_sound.getVolume() - 200*dt,0)) ;
}
void LunarLander::update(float const& dt)
{
	if(m_isAlive)
	{
		updatePosition(dt) ;
		updateRotation(dt) ;
		updateFlame(dt) ;

		clearForce() ;
		addForce( getThrust() ) ;
		addForce( getDrag() ) ;
			
		checkCollision() ;

		if(throttlePushed() && m_fuel > 0) m_fuel -= m_fuelConsumption*dt ;
	}
	updateSound(dt) ;
}

bool LunarLander::throttlePushed() 
{
	if(m_fuel > 0 && Keyboard::isKeyPressed(Keyboard::Up)) return true ;
	else return false ;
}
Vector2f LunarLander::getThrust()
{
	if(throttlePushed() && m_fuel > 0) 
		return Vector2f(m_thrust*sin(getRotation()*(PI/180.f)) , -m_thrust*cos(getRotation()*(PI/180.f)));
	else return Vector2f(0,0) ;
}
Vector2f LunarLander::getDrag() const
{
	return -getSpeed()*m_drag;
}

void LunarLander::updateFlame(float const& dt)
{
	m_flame.setPosition( getPosition() ) ;
	m_flame.setRotation( getRotation() ) ;

	if(throttlePushed() && m_flameLength < 24)
		m_flameLength += 100*dt ;
	else if(throttlePushed() && m_flameLength >= 24)
		m_flameLength = 30 + 3*cos(m_flameTime.getElapsedTime().asSeconds()*50) ;
	else
		m_flameLength = minClamp(m_flameLength - 100*dt, 0) ;
	
	m_flame.setPoint(2, Vector2f(0, m_flameLength) ) ;
}
ConvexShape LunarLander::getFlame() const
{
	return m_flame ;
}

float LunarLander::getFuel() const
{
	return m_fuel ;
}
int LunarLander::getWidth() const
{
	return m_width ;
}
int LunarLander::getHeight() const
{
	return m_height ;
}

bool LunarLander::isAlive() const
{
	return m_isAlive ;
}
bool LunarLander::isWin() const
{
	return m_win ;
}

void LunarLander::reset()
{
	m_isAlive = true ;
	m_win = false ;
}