//This file is part of Lunar Lander (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "GUI.h"

GUI::GUI(int const& _width, int const& _height, LunarLander *_lander, Terrain *_terrain)
{
	width = _width ;
	height = _height ;
	lander = _lander ;
	terrain = _terrain ;

	if(!font.loadFromFile("Ressources/arial.ttf")) cout<<"lol"<<endl;

	screenSpacing = 20 ;
	textSpacing = 30 ;
	
	score.setFont(font) ; score.setCharacterSize(20) ; score.setColor(Color::White) ; 
	time.setFont(font) ; time.setCharacterSize(20) ; time.setColor(Color::White) ; 
	fuel.setFont(font) ; fuel.setCharacterSize(20) ; fuel.setColor(Color::White) ; 
	altitude.setFont(font) ; altitude.setCharacterSize(20) ; altitude.setColor(Color::White) ; 
	hSpeed.setFont(font) ; hSpeed.setCharacterSize(20) ; hSpeed.setColor(Color::White) ; 
	vSpeed.setFont(font) ; vSpeed.setCharacterSize(20) ; vSpeed.setColor(Color::White) ;
	endTxt.setFont(font) ; endTxt.setCharacterSize(30) ; endTxt.setColor(Color::White) ;
}

void GUI::draw(RenderWindow &window)
{
	Vector2f position = lander->getPosition() ;

	score.setPosition(position+Vector2f(screenSpacing-width/2.f,screenSpacing-height/2.f)) ; 
	oss.str("") ; oss.clear() ; oss<<"Score : "<<0 ;
	score.setString(oss.str()) ;

	time.setPosition(position+Vector2f(screenSpacing-width/2.f,screenSpacing-height/2.f+textSpacing)) ; 
	oss.str("") ; oss.clear() ; oss<<"Time : "<<(int)timer.getElapsedTime().asSeconds() ;
	time.setString(oss.str()) ;

	fuel.setPosition(position+Vector2f(screenSpacing-width/2.f,screenSpacing-height/2.f+2*textSpacing)) ; 
	oss.str("") ; oss.clear() ; oss<<"Fuel : "<<(int)lander->getFuel() ;
	fuel.setString(oss.str()) ;

	altitude.setPosition(position+Vector2f(width/2.f-250,screenSpacing-height/2.f)) ; 
	if(lander->isAlive())
	{
		oss.str("") ; oss.clear() ; 
		oss<<"Altitude : "<< (int)(Distance(lander->getPosition(),terrain->getPoint((int)( clamp((lander->getPosition().x-terrain->getCenterPosition().x-lander->getWidth()/2.f)/(float)terrain->getVertexSpacing() ,0,terrain->getSize()-1))))-lander->getHeight()+6) ;
	}
	else 
	{
		oss.str("") ; oss.clear() ; oss<<"Altitude : "<< 0 ; 
	}
	altitude.setString(oss.str()) ;

	hSpeed.setPosition(position+Vector2f(width/2.f-250,screenSpacing-height/2.f+textSpacing)) ; 
	oss.str("") ; oss.clear() ; oss<<"Horizontal Speed : "<<(int)lander->getSpeed().x ;
	hSpeed.setString(oss.str()) ;

	vSpeed.setPosition(position+Vector2f(width/2.f-250,screenSpacing-height/2.f+2*textSpacing)) ; 
	oss.str("") ; oss.clear() ; oss<<"Vertical Speed : "<<(int)lander->getSpeed().y ;
	vSpeed.setString(oss.str()) ;

	if(!lander->isAlive() && lander->isWin()) 
	{
		endTxt.setPosition(position-Vector2f(200,0)) ; 
		oss.str("") ; oss.clear() ; oss<<"You landed succesfully ! Fuel bonus ! " ;
		endTxt.setString(oss.str()) ;
	}
	else if(!lander->isAlive() && !lander->isWin()) 
	{
		endTxt.setPosition(position-Vector2f(200,0)) ; 
		oss.str("") ; oss.clear() ; oss<<"You crashed ! Fuel tank destroyed. " ;
		endTxt.setString(oss.str()) ;
	}

	window.draw(score) ;
	window.draw(time) ;
	window.draw(fuel) ;
	window.draw(altitude) ;
	window.draw(hSpeed) ;
	window.draw(vSpeed) ;
	window.draw(endTxt) ;
}