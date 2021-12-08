#include "pch.h"
#include "Game.h"
#include <iostream>
#include <iomanip>
#include <sstream>

#pragma region gameFunctions
void Start()
{
	InitPlayer(g_Player, g_PlayerGrid);
	InitEnemies(g_Enemies, g_NrEnemies, g_EnemyGrid);

	// Spawn the player
	SpawnCharacter(g_Player, g_PlayerGrid);

	// Example of spawning two enemies
	for (int i = 0; i < 3; i++)
	{
		SpawnCharacter(g_Enemies[i], g_EnemyGrid);
	}
}

void Draw()
{
	ClearBackground(0.5f, 0.0f, 0.7f);
	DrawGrid(g_PlayerGrid);
	DrawGrid(g_EnemyGrid);
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
	switch (key)
	{
	case SDLK_w:
		MoveCharacter(&g_Player, g_PlayerGrid, MovementDirection::up);
		break;
	case SDLK_a:
		MoveCharacter(&g_Player, g_PlayerGrid, MovementDirection::left );
		break;
	case SDLK_s:
		MoveCharacter(&g_Player, g_PlayerGrid, MovementDirection::down);
		break;
	case SDLK_d:
		MoveCharacter(&g_Player, g_PlayerGrid, MovementDirection::right);
		break;
	default:
		break;
	}
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
void InitPlayer(Character& player, Grid& grid)
{
	player.dmg = 100.0f;
	player.dmgMultiplier = 1.0f;
	player.maxHP = player.hp = 500.0f;
	player.isPlayer = true;
	player.isAlive = true;

	std::stringstream stream{};
	stream << std::fixed << std::setprecision(0) << player.maxHP;
	TextureFromString(stream.str(), "resources/LEMONMILK-Medium.otf", 24, Color4f(0.0f, 0.0f, 0.0f), player.healthTexture);

	const Point2f startPos{ (g_WindowWidth / 2.0f) - (grid.width + 25.0f), (g_WindowHeight - grid.height) / 2.0f };
	InitGrid(grid, startPos);
}

void InitEnemies(Character* pEnemies, const int size, Grid& grid)
{
	for (int i = 0; i < size; i++)
	{
		pEnemies[i].dmg = 50.0f;
		pEnemies[i].dmgMultiplier = 1.0f;
		pEnemies[i].maxHP = pEnemies[i].hp = 500.0f;
		pEnemies[i].isPlayer = false;
		pEnemies[i].isAlive = false;

		std::stringstream stream{};
		stream << std::fixed << std::setprecision(0) << pEnemies[i].maxHP;
		TextureFromString(stream.str(), "resources/LEMONMILK-Medium.otf", 24, Color4f(0.0f, 0.0f, 0.0f), pEnemies[i].healthTexture);
	}

	const Point2f startPos{ (g_WindowWidth / 2.0f) + 25.0f, (g_WindowHeight - grid.height) / 2.0f };
	InitGrid(grid, startPos);
}

void InitGrid(Grid& grid, const Point2f& startPos)
{
	const float cellSize{ 96.0f };
	const float spacing{ 10.0f };

	grid.size = 16;
	grid.width = (cellSize + spacing) * 4;
	grid.height = (cellSize + spacing) * 4;
	grid.spacing = spacing;

	for (int i = 0; i < grid.size; i++)
	{
		grid.cells[i].cellPos.x = startPos.x + ((cellSize + spacing) * (i % 4));
		grid.cells[i].cellPos.y = startPos.y + ((cellSize + spacing) * (i / 4));
		grid.cells[i].width = grid.cells[i].height = cellSize;
		grid.cells[i].pCharacter = nullptr;
	}
}

void MoveCharacter(Character* pCharacter, Grid& grid, MovementDirection moveDir)
{
	for (int i = 0; i < grid.size; i++)
	{
		if (grid.cells[i].pCharacter == pCharacter)
		{
			switch (moveDir)
			{
			case MovementDirection::up:
				if (i < 12)
				{
					if (grid.cells[i + 4].pCharacter == nullptr)
					{
						grid.cells[i + 4].pCharacter = grid.cells[i].pCharacter;
						
						grid.cells[i].pCharacter = nullptr;
					}
				}
				break;
			case MovementDirection::down:
				if (i > 3)
				{
					if (grid.cells[i - 4].pCharacter == nullptr)
					{
						grid.cells[i - 4].pCharacter = grid.cells[i].pCharacter;
						grid.cells[i].pCharacter = nullptr;
					}
				}
				break;
			case MovementDirection::left:
				if (i % 4 > 0)
				{
					if (grid.cells[i - 1].pCharacter == nullptr)
					{
						grid.cells[i - 1].pCharacter = grid.cells[i].pCharacter;
						grid.cells[i].pCharacter = nullptr;
					}
				}
				break;
			case MovementDirection::right:
				if (i % 4 < 3)
				{
					if (grid.cells[i + 1].pCharacter == nullptr)
					{
						grid.cells[i + 1].pCharacter = grid.cells[i].pCharacter;
						grid.cells[i].pCharacter = nullptr;
					}
				}
				break;
			default:
				break;
			}
			i = grid.size;
		}
	}
}

void UpdateEnemies(Character* pEnemies, const int size)
{
	if (g_UpdateTimer >= g_EnemyUpdateInterval)
	{
		for (int i = 0; i < size; i++)
		{
			if (pEnemies[i].isAlive)
			{
				if (rand() % 100 < 40)
				{
					MovementDirection randDir{ MovementDirection(rand() % 4) };
					switch (randDir)
					{
					case MovementDirection::up:
						MoveCharacter(&pEnemies[i], g_EnemyGrid, MovementDirection::up);
						break;
					case MovementDirection::down:
						MoveCharacter(&pEnemies[i], g_EnemyGrid, MovementDirection::down);
						break;
					case MovementDirection::left:
						MoveCharacter(&pEnemies[i], g_EnemyGrid, MovementDirection::left);
						break;
					case MovementDirection::right:
						MoveCharacter(&pEnemies[i], g_EnemyGrid, MovementDirection::right);
						break;
					default:
						break;
					}
				}
			}
		}
		g_UpdateTimer = 0.0f;
	}
}

void SpawnCharacter(Character& character, Grid& grid, bool randomSpawn)
{
	if (randomSpawn)
	{
		int index{ int(GenerateRandomNumber(0, grid.size - 1)) };
		while (grid.cells[index].pCharacter != nullptr)
		{
			index = int(GenerateRandomNumber(0, grid.size - 1));
		}

		grid.cells[index].pCharacter = &character;
		character.isAlive = true;
		return;
	}
	else
	{
		for (int i = 0; i < grid.size; i++)
		{
			if (grid.cells[i].pCharacter == nullptr)
			{
				grid.cells[i].pCharacter = &character;
				character.isAlive = true;
				return;
			}
		}
	}
	
	std::cout << "Unable to spawn character" << std::endl;
}

void HitCharacter(Character& character, const float dmg)
{

}

void KillCharacter(Character& character, Grid& grid)
{

}

void ShootProjectille(const Cell& originCell, const MovementDirection& moveDir, Projectille* pProjectilles, const int size)
{
}

void ShootRay(const Cell& originCell, const MovementDirection& moveDir)
{
}

void UpdateProjectilles(Projectille* pProjectilles, const int size)
{
}

void DrawGridCharacters(Grid& grid)
{
	for (int i = 0; i < grid.size; i++)
	{
		if (grid.cells[i].pCharacter == nullptr) continue;

		if (grid.cells[i].pCharacter->isAlive)
		{
			if (grid.cells[i].pCharacter->isPlayer)
			{
				SetColor(0.2f, 1.0f, 0.2f);
			}
			else
			{
				SetColor(1.0f, 0.2f, 0.2f);
			}

			FillRect(grid.cells[i].cellPos.x + 8.0f, grid.cells[i].cellPos.y + 8.0f, grid.cells[i].width - 16.0f, grid.cells[i].height - 16.0f);
			const Point2f textPos{grid.cells[i].cellPos.x + ((grid.cells[i].width / 2.0f) - (grid.cells[i].pCharacter->healthTexture.width / 2.0f)), grid.cells[i].cellPos.y + 8.0f};
			DrawTexture(grid.cells[i].pCharacter->healthTexture, textPos);
		}
	}
}

void DrawGrid(Grid& grid)
{
	for (int i = 0; i < grid.size; i++)
	{
		SetColor(0.9f, 0.9f, 0.9f);
		FillRect(grid.cells[i].cellPos, grid.cells[i].width, grid.cells[i].height);

		SetColor(0.0f, 0.0f, 0.0f);
		DrawRect(grid.cells[i].cellPos, grid.cells[i].width, grid.cells[i].height, 3.0f);
	}

	DrawGridCharacters(grid);
}
#pragma endregion ownDefinitions