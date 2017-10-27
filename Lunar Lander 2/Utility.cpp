//This file is part of Lunar Lander (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

using namespace sf ;
using namespace std ;

void interpolation(float &x, float const& y, float const& time, float const& deltaTime)
{
	x += (2.f*(y-x)*deltaTime)/time ;
}

float determinant(Vector2f const& u, Vector2f const& v) 
{
	float result = u.x*v.y - u.y*v.x ;
	return result ;
}

float dotProduct(Vector2f const& u, Vector2f const& v)
{
	return u.x*v.x + u.y*v.y ;
}

float Angle(Vector2f const& v1, Vector2f const& v2)
{
	float angle = atan2(determinant(v1,v2), dotProduct(v1,v2))*180/PI ;
	if(angle<0)
		angle = 360 + angle ;
	return angle ;
}

void drawPoint(Vector2f const& p, float const& radius, RenderWindow &window, Color const& color)
{
	CircleShape c(radius) ;
	c.setFillColor(color) ;
	c.setPosition(p) ;
	c.setOrigin(radius,radius) ;
	window.draw(c) ;
}

void drawLine(Vector2f const& pos, Vector2f const& dir, RenderWindow &window, Color const& color)
{
	VertexArray line(Lines, 2) ;
	line[0].position = pos ;
	line[0].color = color ;
	line[1].position = dir+pos ;
	line[1].color = color ;
	window.draw(line) ;
}

float Distance(Vector2f const& u, Vector2f const& v)
{
	return sqrt(pow(u.x-v.x,2)+pow(u.y-v.y,2)) ;
}

Vector2f rotatePoint(Vector2f const& point, Vector2f const& center, float const& angle) 
{
	float x = center.x + (point.x - center.x)*cos(angle*(PI/180)) - (point.y - center.y)*sin(angle*(PI/180)) ;
	float y = center.y + (point.x - center.x)*sin(angle*(PI/180)) + (point.y - center.y)*cos(angle*(PI/180)) ;
	return Vector2f(x,y) ;
}

float Norm (Vector2f const& v) 
{
	float result = sqrt(pow(v.x,2)+pow(v.y,2)) ;
	return result ;
}

bool mouseClickedOnce(Mouse::Button const& button, bool &clickedLastFrame) 
{
	bool result = false ;
	if(Mouse::isButtonPressed(button) && clickedLastFrame == false)
	{
		result = true ;
		clickedLastFrame = true ;
	}
	else if (Mouse::isButtonPressed(button) && clickedLastFrame == true) 
	{
		result = false ;
		clickedLastFrame = true ;
	}
	else
	{
		result = false ;
		clickedLastFrame = false ;
	}
	return result ;
}

float clamp(float value, float min, float max) 
{
	float result ;
	if(value > max)
		result = max ;
	else if(value < min)
		result = min ;
	else
		result = value ;
	return result ;
}
float minClamp(float value, float min) 
{
	float result ;
	if(value < min)
		result = min ;
	else
		result = value ;
	return result ;
}
float maxClamp(float value, float max) 
{
	float result ;
	if(value > max)
		result = max ;
	else
		result = value ;
	return result ;
}

bool checkSegmentIntersection(Vector2f const& A, Vector2f const& B, Vector2f const& C, Vector2f const& D)
{
	if(determinant(B-A,C-A)*determinant(B-A,D-A)<0 && determinant(D-C,A-C)*determinant(D-C,B-C)<0)
		return true ;
	return false ;
}
bool collisionTrianglePoint(Vector2f const& a, Vector2f const& b, Vector2f const& c, Vector2f const& point) 
{
	Vector2f ab = b-a ;
	Vector2f bc = c-b ;
	Vector2f ca = a-c ;
	
	if(determinant(ab,point-a) > 0 && determinant(bc,point-b) > 0 && determinant(ca,point-c) > 0)
	{
		return true ;
	}
	else return false ;
}

Vector2f randVector2f(float const& among)
{
	return Vector2f((rand()%RAND_MAX/(float)RAND_MAX-0.5)*among,(rand()%RAND_MAX/(float)RAND_MAX-0.5)*among) ; 
}
vector<int> readCfgFile(string path)
{
	ifstream cfg(path) ;
	string line ;
	vector<int> result ;
	int intBuf ;
	string strBuf ;
	
	cfg>>strBuf>>intBuf ;
	result.push_back(intBuf) ;

	while(getline(cfg, line))
	{
		cfg.ignore() ;
		cfg>>strBuf>>intBuf ;
		result.push_back(intBuf) ;
	}
	return result ;
}