#pragma once
using namespace utils;
#pragma region gameInformation
std::string g_WindowTitle{ "Untitled Grid Game - Arno - Jef - 1DAE21" };

float g_WindowWidth{ 1280 };
float g_WindowHeight{ 720 };
#pragma endregion gameInformation


#pragma region ownDeclarations
float g_DeltaTime{};
enum class GameState
{
	Start
	,Active
	,GameOver
};
GameState g_GameState{ GameState::Start };

const float g_EnemyUpdateInterval{ .75f };
Point2f g_EnemySpawnInterval{ 1.0f, 4.5f };
float g_UpdateTimer{ 0.0f };
float g_SpawnTimer{ GenerateRandomNumber(g_EnemySpawnInterval.x, g_EnemySpawnInterval.y)};

const int g_NrRays{ 255 };
Ray g_Rays[g_NrRays]{};

Grid g_PlayerGrid{};
Grid g_EnemyGrid{};

const int g_NrEnemies{ 16 };
Character g_Player{};
Character g_Enemies[g_NrEnemies]{};

const int g_NrProjectilles{ 50 };
Projectille g_Projectilles[g_NrProjectilles]{};

void InitPlayer(Character& player, Grid& grid);
void InitEnemies(Character* pEnemies, const int size, Grid& grid);

void InitGrid(Grid& grid, const Point2f& startPos);

void InitStartConfig();

void MoveCharacter(Character* character, Grid& grid, MovementDirection moveDir);

void SpawnCharacter(Character* pCharacter, Grid& grid, bool randomSpawn = true);
void DamageCharacter(Character* pCharacter, const float dmg);
void KillCharacter(Character* pCharacter, Grid& grid);

bool IsInView(const Point2f& pos, const float size);

void ShootProjectille(const Character* pCharacter, Projectille* pProjectilles, const int size);

void ShootRay(const Character& caster, const MovementDirection& moveDir);
void AddRay(const Ray* pRay);
void DrawRays(Ray* pRays, const int size);

void UpdateProjectilles(Projectille* pProjectilles, const int size);

void UpdateEnemies(Character* pEnemies, const int size);
void SpawnEnemy(Character* pEnemies, const int size);
void UpdateCharacterHealthTexture(Character* pCharacter);

void DrawStartScreen();
void DrawGameOverScreen();
void DrawGridCharacters(Grid& grid);
void DrawGrid(Grid& grid);
void DrawProjectilles(Projectille* pProjectilles, const int size);
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
