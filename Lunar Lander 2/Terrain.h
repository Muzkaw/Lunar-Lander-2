//This file is part of Lunar Lander (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace sf ;
using namespace std ;

class Terrain
{
public:
	Terrain(int const& _vertexSpacing,  float const& _terrainSize, Vector2f const& _centerPosition);
	
	VertexArray getTerrain() const ;
	int getVertexSpacing() const ;
	int getSize() const ;
	Vector2f getPoint(int const& i) const ;
	Vector2f getCenterPosition() const ;

	void draw(RenderWindow &window) ;

private:
	int vertexSpacing ;
	float terrainSize ;
	Vector2f centerPosition ;
	VertexArray terrain ;
};