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
// Grid game Constructors
//-----------------------------------------------------------------
Character::Character()
	:Character{ Point2f(), Texture(), Texture(), 100.0f, 100.0f, 100.0f, 1.0f, false, false }
{
}

Character::Character(const Point2f& pos, const Texture& characterTexture, const Texture& healthTexture, const float hp, const float maxHP, const float dmg, const float dmgMultiplier, const bool isPlayer, const bool isAlive)
	: pos{pos}
	, characterTexture{ characterTexture }
	, healthTexture{ healthTexture }
	, hp{ hp }
	, maxHP{ maxHP }
	, dmg{ dmg }
	, dmgMultiplier{ dmgMultiplier }
	, isPlayer{ isPlayer }
	, isAlive{ isAlive }
{
}

Cell::Cell()
	:Cell{new Character(), Point2f(), 64.0f, 64.0f, true}
{
}

Cell::Cell(Character* occupyingCharacter, const Point2f& cellPos, const float width, const float height, const bool isWalkable)
	: pCharacter{ occupyingCharacter }
	, cellPos{cellPos}
	, width{width}
	, height{height}
	, isWalkable{isWalkable}
{
}

Grid::Grid()
	:Grid{Cell(), 424.0f, 424.0f, 10.0f, 16}
{
}

Grid::Grid(const Cell& cells, const float width, const float height, const float spacing, const int size)
	: cells{cells}
	, width{width}
	, height{height}
	, spacing{ spacing }
	, size{size}
{
}

Projectille::Projectille()
	:Projectille{ Point2f(), MovementDirection::left, false, 1.0f, 10.0f, 10.0f }
{
}

Projectille::Projectille(const Point2f& pos, const MovementDirection& moveDir, const bool inScene, const float dmg, const float speed, const float size)
	: pos{pos}
	, moveDir{moveDir}
	, inScene{inScene}
	, dmg{dmg}
	, speed{ speed }
	, size{ size }
{
}

Ray::Ray()
	:Ray{ Point2f(), MovementDirection::right, Color4f(), Rectf(), 0.0f, 1.0f, 100.0f }
{
}

Ray::Ray(const Point2f& startPos, const MovementDirection& moveDir, const Color4f& color, const Rectf& graphic, const float duration, const float dmg, const float range)
	: startPos{startPos}
	, moveDir{moveDir}
	, color{color}
	, graphic{graphic}
	, duration{duration}
	, dmg{dmg}
	, range{range}
{
}
