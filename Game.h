#pragma once
using namespace std;
#include <stack>
#include "Player.h"
#include "Projectile.h"
#include "Chicken.h"
#include "PowerUp.h"
#include "string"
#include <time.h>
#include <gl/glut.h>

class Game
{
public:
	Player player;
	stack<Projectile> projectiles;
	stack<Projectile> tempProjectiles;
	stack<Chicken> chickenBucket;
	stack<Chicken> tempBucket;
	stack<PowerUp> powerUps;
	stack<PowerUp> tempPowerUps;
	
	int gameMode;

	int maxProjectiles = 128;
	int maxChickens = 256;
	int maxPowerUps = 4;

	int currentScene = 0;
	float chickenTimer = 0;
	float starTimer = 0;
	int totalSpawnedChickens = 0;

	bool bossAlive = false;
	int bossKills = 0;
	float lastBossKillTime = glutGet(GLUT_ELAPSED_TIME);
	float roundWaitTime = 4000;

	int initial_time = time(NULL), final_time, frame_count;
	int framerate = 0;

	float shotCD = 190;
	float lastShotTime = glutGet(GLUT_ELAPSED_TIME);

	float timeSinceLastPowerUpPickUp = glutGet(GLUT_ELAPSED_TIME);
	float powerUpCD = 7000;

	Game();
	Game(Player p, int gameMode);
	void setPlayer(Player p);

	void createProjectile(float position[2], float velocity[2], float color[3],
		float life, int sourceID, float dimensions[2], float hitboxDimensions[2]);
	void drawProjectiles();

	void createChicken(float position[2], float velocity[2], float color[3],
		float health, float maxHealth, float dimensions[2], float hitboxDimensions[2], int Type);
	void drawChickens();

	void createPowerUp(float position[2]);
	void drawPowerUps();

	void drawStartScreen();
	void drawPlayerStats();
	void drawDeathScreen();
	void drawText(const char* text, int length, int x, int y);

	void spawnChickens();
	void spawnChickenBoss();
	void spawnPowerUps();

	void checkForDeath();
	void checkCollisions();
};

