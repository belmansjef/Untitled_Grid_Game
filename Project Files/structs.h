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
	explicit Character(const Point2f& pos, const Texture& characterTexture, const Texture& healthTexture, const float hp, const float maxHP, const float dmg, const float dmgMultiplier, const bool isPlayer, const bool isAlive);
	
	Point2f pos;

	Texture characterTexture;
	Texture healthTexture;

	bool isAlive;
	bool isPlayer;

	float hp;
	float maxHP;

	float dmg;
	float dmgMultiplier;
};

struct Cell
{
	Cell();
	explicit Cell(Character* occupyingCharacter, const Point2f& cellPos, const float width, const float height, const bool isWalkable);

	Character* pCharacter;

	Point2f cellPos;
	bool isWalkable;

	float width;
	float height;
};

struct Grid
{
	Grid();
	explicit Grid(const Cell& cells, const float width, const float height, const float spacing, const int size);

	Cell cells[16];
	int size;

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
	explicit Projectille(const Point2f& pos, const MovementDirection& moveDir, const bool inScene, const float dmg, const float speed, const float size);
	
	Point2f pos;
	MovementDirection moveDir;

	bool inScene;

	float dmg;
	float speed;
	float size;
};

struct Ray
{
	Ray();
	explicit Ray(const Point2f& startPos, const MovementDirection& moveDir, const Color4f& color, const Rectf& graphic, const float duration, const float dmg, const float range);

	Point2f startPos;
	MovementDirection moveDir;
	Color4f color;

	Rectf graphic;
	float duration;

	float dmg;
	float range;
};
