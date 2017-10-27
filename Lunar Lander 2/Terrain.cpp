//This file is part of Lunar Lander (GNU GPL) - https://www.youtube.com/user/Muzkaw).

#include "Terrain.h"

Terrain::Terrain(int const& _vertexSpacing,  float const& _terrainSize, Vector2f const& _centerPosition)
{
	terrain.clear() ;

	vertexSpacing = _vertexSpacing ;
	terrainSize = _terrainSize ;
	centerPosition = _centerPosition ;

	terrain.setPrimitiveType(LinesStrip) ;
	int vertexCount = (int)(terrainSize/(float)vertexSpacing) ;
	terrain.append(Vertex(centerPosition,Color::White)) ;

	srand(time(NULL)) ;
	vector<float> slopeDirection ; slopeDirection.push_back(-1) ;
	int slopeDirectionRand ;
	
	for(int i(1) ; i < vertexCount ; i++)
	{
		slopeDirectionRand = rand()%100 ;
		if(slopeDirectionRand < 10)
		{
			slopeDirection.push_back( ((rand()%RAND_MAX)/(float)RAND_MAX-0.5f)*3 ) ;
		}
		else
			slopeDirection.push_back( slopeDirection[i-1] ) ;
		
	}
	for(int i(1) ; i < vertexCount ; i++)
	{
		terrain.append( Vertex( Vector2f( i*vertexSpacing + centerPosition.x  , terrain[i-1].position.y + (float)(rand()%20)*slopeDirection[i] ) , Color::White ) ) ;
	}
}

VertexArray Terrain::getTerrain() const
{
	return terrain ;
}
int Terrain::getVertexSpacing() const
{
	return vertexSpacing ;
}
int Terrain::getSize() const
{
	return terrain.getVertexCount() ;
}
Vector2f Terrain::getPoint(int const& i) const
{
	return terrain[i].position ;
}
Vector2f Terrain::getCenterPosition() const
{
	return centerPosition ;
}

void Terrain::draw(RenderWindow &window)
{
	window.draw(terrain) ;
}