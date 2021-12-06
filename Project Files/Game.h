#pragma once
using namespace utils;
#pragma region gameInformation
std::string g_WindowTitle{ "Untitled Grid Game - Arno - Jef - 1DAE21" };

float g_WindowWidth{ 1280 };
float g_WindowHeight{ 720 };
#pragma endregion gameInformation


#pragma region ownDeclarations
Grid g_PlayerGird{};
Grid g_EnemyGrid{};

const int g_NrEnemies{ 16 };
Character g_Player{};
Character g_Enemies[g_NrEnemies]{};

void InitPlayerGrid(Grid* pPlayerGrid);
void InitEnemyGrid(Grid* pEnemyGrid);

void InitPlayer(Character& player);
void InitEnemies(Character* pEnemies, const int size);
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
