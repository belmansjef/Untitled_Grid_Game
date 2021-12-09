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

	// Example of spawning three enemies
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

	DrawProjectilles(g_Projectilles, g_NrProjectilles);
}

void Update(float elapsedSec)
{
	g_DeltaTime = elapsedSec;

	g_UpdateTimer += g_DeltaTime;
	g_SpawnTimer += g_DeltaTime;

	UpdateEnemies(g_Enemies, g_NrEnemies);
	UpdateProjectilles(g_Projectilles, g_NrProjectilles, elapsedSec);
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
	case SDLK_SPACE:
		ShootRay(g_Player, MovementDirection::right);
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
	player.isAlive = false;

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
			break;
		}
	}

	for (int i = 0; i < grid.size; i++)
	{
		if (grid.cells[i].pCharacter != nullptr)
		{
			grid.cells[i].pCharacter->pos = grid.cells[i].cellPos;
		}
	}

	if (!pCharacter->isPlayer)
	{
		ShootProjectille(pCharacter, g_Projectilles, g_NrProjectilles);
	}
}

void UpdateEnemies(Character* pEnemies, const int size)
{
	if (g_UpdateTimer >= g_EnemyUpdateInterval)
	{
		bool attemptSpawnEnemy{ false };
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
			if (!attemptSpawnEnemy)
			{
				if (!pEnemies[i].isAlive)
				{
					attemptSpawnEnemy = !attemptSpawnEnemy;
					if (rand() % 100 < 6)
					{
						SpawnCharacter(*pEnemies, g_EnemyGrid, true);
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
		character.pos = grid.cells[index].cellPos;
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
				character.pos = grid.cells[i].cellPos;
				character.isAlive = true;
				return;
			}
		}
	}
	
	std::cout << "Unable to spawn character" << std::endl;
}

void DamageCharacter(Character* pCharacter, const float dmg)
{
	pCharacter->hp -= dmg;
	if (pCharacter->hp <= 0.0f)
	{
		pCharacter->hp = 0.0f;

		Grid grid = pCharacter->isPlayer ? g_PlayerGrid : g_EnemyGrid;
		KillCharacter(pCharacter, grid);
	}

	DeleteTexture(pCharacter->healthTexture);

	std::stringstream stream{};
	stream << std::fixed << std::setprecision(0) << pCharacter->hp;
	TextureFromString(stream.str(), "resources/LEMONMILK-Medium.otf", 24, Color4f(0.0f, 0.0f, 0.0f), pCharacter->healthTexture);
}

void KillCharacter(Character* pCharacter, Grid& grid)
{
	if (pCharacter->isPlayer)
	{
		// TODO: End of round
		return;
	}

	for (int i = 0; i < grid.size; i++)
	{
		if (grid.cells[i].pCharacter == pCharacter && grid.cells[i].pCharacter)
		{
			grid.cells[i].pCharacter->isAlive = false;
			grid.cells[i].pCharacter = nullptr;
		}
	}
	
}

bool IsInView(const Point2f& pos, const float size)
{
	return pos.x + size > 0 && pos.x - size < g_WindowWidth&& pos.y + size > 0 && pos.y - size < g_WindowHeight;
}

void ShootProjectille(const Character* pCharacter, Projectille* pProjectilles, const int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!pProjectilles[i].inScene)
		{
			pProjectilles[i].moveDir = pCharacter->isPlayer ? MovementDirection::right : MovementDirection::left;
			pProjectilles[i].size = 20.0f;
			pProjectilles[i].speed = 10.0f;
			pProjectilles[i].pos.x = (pCharacter->pos.x + 48.0f) - pProjectilles[i].size / 2.0f;
			pProjectilles[i].pos.y = (pCharacter->pos.y + 48.0f) - pProjectilles[i].size / 2.0f;

			pProjectilles[i].dmg = pCharacter->dmg;
			pProjectilles[i].inScene = true;
			
			return;
		}
	}
}

void ShootRay(const Character& caster, const MovementDirection& moveDir)
{
	Ray ray{ caster.pos, moveDir, Color4f(1.0f, 0.2f, 0.2f), caster.dmg, 250.0f };
	Grid otherGrid{ caster.isPlayer ? g_EnemyGrid : g_PlayerGrid};

	for (int i = 0; i < otherGrid.size; i++)
	{
		Character* target{ otherGrid.cells[i].pCharacter };
		if (target && target->pos.y == ray.startPos.y)
		{
			DamageCharacter(target, ray.dmg);
			std::cout << "Hit at " << i << " !" << std::endl;
		}
	}
}

void UpdateProjectilles(Projectille* pProjectilles, const int size, const float elapsedSec)
{
	const Rectf playerRect{ g_Player.pos.x, g_Player.pos.y, 80.0f, 80.0f };
	
	for (int i = 0; i < size; i++)
	{
		if (pProjectilles[i].inScene)
		{
			const Rectf projectilleRect{pProjectilles[i].pos.x, pProjectilles[i].pos.y, pProjectilles[i].size, pProjectilles[i].size};
			switch (pProjectilles[i].moveDir)
			{
			case MovementDirection::left:
				pProjectilles[i].pos.x -= 1.0f;
			case MovementDirection::right:
				pProjectilles[i].pos.x += pProjectilles[i].speed * g_DeltaTime;
			default:
				break;
			}

			if (IsOverlapping(playerRect, projectilleRect))
			{
				DamageCharacter(&g_Player, pProjectilles[i].dmg);
				pProjectilles[i].inScene = false;
				continue;
			}

			pProjectilles[i].inScene = IsInView(pProjectilles[i].pos, pProjectilles[i].size);
		}
	}
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

void DrawProjectilles(Projectille* pProjectilles, const int size)
{
	SetColor(1.0f, 0.1f, 0.1f);
	for (int i = 0; i < size; i++)
	{
		if (pProjectilles[i].inScene)
		{
			const Rectf projectilleRect{ pProjectilles[i].pos.x, pProjectilles[i].pos.y, pProjectilles[i].size, pProjectilles[i].size };
			FillRect(projectilleRect);
		}
	}
}
#pragma endregion ownDefinitions