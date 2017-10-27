//This file is part of Lunar Lander(GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream> 
#include <sstream>
#include "LunarLander.h"
#include "Terrain.h" 
#include "Utility.h"

using namespace sf ;
using namespace std ;

class GUI
{
public:
	GUI(int const& _width, int const& _height, LunarLander *_lander, Terrain *_terrain);

	void draw(RenderWindow &window) ;

private:
	int width ;
	int height ;
	float screenSpacing, textSpacing ;
	LunarLander *lander ;
	Terrain *terrain ;
	Clock timer ;

	Font font ;
	ostringstream oss ;
	Text score, time, fuel, altitude, hSpeed, vSpeed, endTxt ;
};

