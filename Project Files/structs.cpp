#include "pch.h"
#include "structs.h"

//-----------------------------------------------------------------
// Window Constructors
//-----------------------------------------------------------------
Window::Window( const std::string& title , float width , float height , bool isVSyncOn )
	:title{ title }
	,width{ width }
	,height{ height }
	,isVSyncOn{ isVSyncOn }
{
}

//-----------------------------------------------------------------
// Point2f Constructors
//-----------------------------------------------------------------
Point2f::Point2f( )
	:Point2f{ 0.0f, 0.0f }
{
}
Point2f::Point2f( float x, float y )
	:x{ x }, y{ y }
{
}

//-----------------------------------------------------------------
// Line4f Constructors
//-----------------------------------------------------------------
Line4f::Line4f()
	:Line4f {0.0f, 0.0f, 0.0f, 0.0f}
{
}

Line4f::Line4f(float x1, float y1, float x2, float y2)
	:Line4f{Point2f(x1, y1), Point2f(x2, y2)}
{
}

Line4f::Line4f(Point2f p1, Point2f p2)
	:p1{ p1 }, p2{ p2 }
{
}

//-----------------------------------------------------------------
// Rectf Constructors
//-----------------------------------------------------------------
Rectf::Rectf( )
	:Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Rectf::Rectf( float left, float bottom, float width, float height )
	:left{ left }
	,bottom{ bottom }
	,width{ width }
	,height{ height }
{
}

//-----------------------------------------------------------------
// Color4f Constructors
//-----------------------------------------------------------------
Color4f::Color4f( )
	:Color4f{ 0.0f, 0.0f, 0.0f, 1.0f }
{
}

Color4f::Color4f( float r, float g, float b, float a )
	:r{ r }
	,g{ g }
	,b{ b }
	,a{ a }
{
}

//-----------------------------------------------------------------
// Circlef Constructors
//-----------------------------------------------------------------
Circlef::Circlef( )
	:Circlef{ 0.0f, 0.0f, 0.0f }
{
}

Circlef::Circlef( float centerX, float centerY, float radius )
	:Circlef{ Point2f{ centerX, centerY }, radius }
{
}

Circlef::Circlef( const Point2f& center, float radius )
	:center{ center }
	,radius{ radius }
{
}

//-----------------------------------------------------------------
// Ellipsef Constructors
//-----------------------------------------------------------------
Ellipsef::Ellipsef( )
	:Ellipsef{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Ellipsef::Ellipsef( float centerX, float centerY, float radiusX, float radiusY )
	: Ellipsef{ Point2f{ centerX, centerY }, radiusX, radiusY }
{
}

Ellipsef::Ellipsef(const Point2f& center, float radiusX, float radiusY)
	: center{ center }
	, radiusX{ radiusX }
	, radiusY{ radiusY }
{
}

//-----------------------------------------------------------------
// Cell Constructors
//-----------------------------------------------------------------
Cell::Cell()
	:Cell{Character(), Point2f(), true}
{
}
Cell::Cell(const Character& occupyingChar, const Point2f& cellPos, const bool isValid)
	: occupyingChar{occupyingChar}
	, cellPos{cellPos}
	, isValid{isValid}
{
}

Character::Character()
	:Character{Texture(), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
{
}

Character::Character(const Texture& charTexture, const float hp, const float maxHP, const bool isPlayer, const float dmgMultiplier, const float dmg)
	: charTexture{charTexture}
	, hp{hp}
	, maxHP{maxHP}
	, isPlayer{ isPlayer }
	, dmgMultiplier{ dmgMultiplier }
	, dmg{dmg}
{
}

Grid::Grid()
	:Grid{Cell(), 0.0f, 0.0f, 16}
{
}

Grid::Grid(const Cell& gridCells, const float width, const float height, const int size)
	: gridCells{gridCells}
	, width{width}
	, height{height}
	, size{size}
{
}
