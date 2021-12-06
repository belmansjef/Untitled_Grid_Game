#pragma once
using namespace utils;
#pragma region gameInformation
std::string g_WindowTitle{ "Untitled Grid Game - Arno - Jef - 1DAE21" };

float g_WindowWidth{ 1280 };
float g_WindowHeight{ 720 };
#pragma endregion gameInformation


#pragma region ownDeclarations
const float g_EnemyUpdateInterval{ 2.0f };
Point2f g_EnemySpawnInterval{ 2.0f, 30.0f };
float g_UpdateTimer{};
float g_SpawnTimer{};

Grid g_PlayerGrid{};
Grid g_EnemyGrid{};

const int g_NrEnemies{ 16 };
Character g_Player{};
Character g_Enemies[g_NrEnemies]{};

void InitPlayerGrid(Grid& playerGrid);
void InitEnemyGrid(Grid& enemyGrid);

void InitPlayer(Character& player);
void InitEnemies(Character* pEnemies, const int size);

void MovePlayer(Character& player, MovementDirection moveDir);
void MoveEnemy(Character& enemy, MovementDirection moveDir);

void UpdateEnemies(Character* pEnemies, const int size);
void SpawnEnemies(Character* pEnemies, const int size, const int emeniesToSpawn);

void DrawGrid(Grid& grid);

void DrawPlayer(Character& player);
void DrawEnemies(Grid& enemyGrid);
#pragma endregion ownDeclarations

#pragma region gameFunctions			
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
