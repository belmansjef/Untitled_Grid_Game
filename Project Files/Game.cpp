#include "pch.h"
#include "Game.h"
#include <iostream>

#pragma region gameFunctions
void Start()
{
	InitPlayerGrid(g_PlayerGrid);
}

void Draw()
{
	ClearBackground(0.0f, 0.0f, 0.0f);
	DrawGrid(g_PlayerGrid);
}

void Update(float elapsedSec)
{
	g_UpdateTimer += elapsedSec;
	g_SpawnTimer += elapsedSec;
	UpdateEnemies(g_Enemies, g_NrEnemies);
}

void End()
{

}
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{

}
#pragma endregion inputHandling

#pragma region ownDefinitions
void InitPlayerGrid(Grid& playerGrid)
{
	const Point2f startPos{ 20.0f, g_WindowHeight / 3.0f };
	const float cellSize{ 64.0f };
	const float spacing{ 10.0f };

	playerGrid.size = 16;
	playerGrid.width = (cellSize + spacing) * 4;
	playerGrid.height = (cellSize + spacing) * 4;
	playerGrid.spacing = spacing;

	for (int i = 0; i < playerGrid.size; i++)
	{
		playerGrid.cells[i].cellPos.x = startPos.x + ((cellSize + spacing) * (i % 4));
		playerGrid.cells[i].cellPos.y = startPos.y + ((cellSize + spacing) * (i / 4));
		playerGrid.cells[i].width = playerGrid.cells[i].height = cellSize;
	}
}
void InitEnemyGrid(Grid* pEnemyGrid)
{
}
void InitPlayer(Character& player)
{
}
void InitEnemies(Character* pEnemies, const int size)
{
}
void MovePlayer(Character& player, MovementDirection moveDir)
{
}
void MoveEnemy(Character& enemy, MovementDirection moveDir)
{
}
void UpdateEnemies(Character* pEnemies, const int size)
{
	if (g_UpdateTimer >= g_EnemyUpdateInterval)
	{
		// TODO: enemy logic
		g_UpdateTimer = 0.0f;
	}
}
void SpawnEnemies(Character* pEnemies, const int size, const int emeniesToSpawn)
{
}
void DrawGrid(Grid& grid)
{
	for (int i = 0; i < grid.size; i++)
	{
		SetColor(1.0f, 1.0f, 1.0f);
		FillRect(grid.cells[i].cellPos, grid.cells[i].width, grid.cells[i].height);
	}
}
void DrawPlayer(Character& player)
{
}
void DrawEnemies(Grid& enemyGrid)
{
}
#pragma endregion ownDefinitions