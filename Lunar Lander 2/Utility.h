//This file is part of Lunar Lander (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <fstream>

#define PI 3.14159265359

using namespace sf ;
using namespace std ;

void interpolation(float &x, float const& y, float const& time, float const& deltaTime);
float determinant(Vector2f const& u, Vector2f const& v) ;
float dotProduct(Vector2f const& u, Vector2f const& v) ;
float Angle(Vector2f const& v1, Vector2f const& v2) ;
int interpolation(int& x, int const& y, float const& time, float const& deltaTime) ;
void drawPoint(Vector2f const& p, float const& radius, RenderWindow &window, Color const& color) ;
void drawLine(Vector2f const& pos, Vector2f const& dir, RenderWindow &window, Color const& color) ;
float Distance(Vector2f const& u, Vector2f const& v) ;
Vector2f rotatePoint(Vector2f const& point, Vector2f const& center, float const& angle) ;
float Norm (Vector2f const& v) ;
bool mouseClickedOnce(Mouse::Button const& button, bool &clickedLastFrame) ;
float clamp(float value, float min, float max) ;
float minClamp(float value, float min) ;
float maxClamp(float value, float max) ;
bool checkSegmentIntersection(Vector2f const& A, Vector2f const& B, Vector2f const& C, Vector2f const& D) ;
bool collisionTrianglePoint(Vector2f const& a, Vector2f const& b, Vector2f const& c, Vector2f const& point) ;
Vector2f randVector2f(float const& among) ;
vector<int> readCfgFile(string path) ;
