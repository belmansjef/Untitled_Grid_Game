#pragma once
#include <string>


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

struct Texture
{
	GLuint id;
	float width;
	float height;
};

struct Character
{
	Character();
	explicit Character(const Texture& charTexture, const int cellIndex, const float hp, const float maxHP, const float dmgMultiplier, const float dmg, const bool isPlayer, const bool isActive);
	
	bool isActive;
	bool isPlayer;
	int cellIndex;
	Texture charTexture;
	float hp;
	float maxHP;
	float dmgMultiplier;
	float dmg;
};

struct Cell
{
	Cell();
	explicit Cell(const int occupyingCharIndex, const Point2f& cellPos, const float width, const float height, const bool isValid);

	bool isValid;
	int occupyingCharIndex;
	Point2f cellPos;
	float width;
	float height;
};

struct Grid
{
	Grid();
	explicit Grid(const Cell& cells, const float width, const float height, const float spacing, const int size);

	int size;
	Cell cells[16];
	float width;
	float height;
	float spacing;
};

enum class MovementDirection
{
	up,
	down,
	left,
	right
};

struct Projectille
{
	Projectille();
	explicit Projectille(const Point2f& pos, const MovementDirection& moveDir, const float dmg, const float speed, const float size);
	
	Point2f pos;
	MovementDirection moveDir;
	float dmg;
	float speed;
	float size;
};
