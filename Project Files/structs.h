#pragma once
#include <string>
#include "utils.h"
using namespace utils;

struct Window
{
	explicit Window( const std::string& title = "Title", float width = 320.0f, 
		float height = 180.0f, bool isVSyncOn = true );

	std::string title;
	float width;
	float height;
	bool isVSyncOn;
};

struct Point2f
{
	Point2f( );
	explicit Point2f( float x, float y );

	float x;
	float y;
};

struct Line4f
{
	Line4f( );
	explicit Line4f(Point2f p1, Point2f p2);
	explicit Line4f(float x1, float y1, float x2, float y2);

	Point2f p1;
	Point2f p2;
};

struct Rectf
{
	Rectf( );
	explicit Rectf( float left, float bottom, float width, float height );
	
	float left;
	float bottom;
	float width;
	float height;

};


struct Color4f
{
	Color4f( );
	explicit Color4f( float r, float g, float b, float a = 1.0f );
	
	float r;
	float g;
	float b;
	float a;
};

struct Circlef
{
	Circlef( );
	explicit Circlef( const Point2f& center, float radius );
	explicit Circlef( float centerX, float centerY, float radius );

	Point2f center;
	float radius;
};


struct Ellipsef
{
	Ellipsef( );
	explicit Ellipsef( const Point2f& center, float radiusX, float radiusY );
	explicit Ellipsef( float centerX, float centerY, float radiusX, float radiusY );

	Point2f center;
	float radiusX;
	float radiusY;
};

struct Character
{
	Character();
	explicit Character(const Texture& charTexture, const float hp, const float maxHP, const float dmgMultiplier, const float dmg, const bool isPlayer, const bool isInitalized);
	
	bool isInitialized;
	bool isPlayer;
	Texture charTexture;
	float hp;
	float maxHP;
	float dmgMultiplier;
	float dmg;
};

struct Cell
{
	Cell();
	explicit Cell(const int occupyingCharIndex, const Point2f& cellPos, const bool isValid);

	bool isValid;
	int occupyingCharIndex;
	Point2f cellPos;
};

struct Grid
{
	Grid();
	explicit Grid(const Cell& gridCells, const float width, const float height, const int size);

	int size;
	Cell gridCells[16];
	float width;
	float height;
};

struct Projectille
{
	Projectille();
	explicit Projectille(const Point2f& pos, const float dmg, const float speed, const float radius);
	
	Point2f pos;
	float dmg;
	float speed;
	float radius;
};
