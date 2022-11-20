#pragma once
#include <gl/glut.h>
class Player
{
public:
	float position[2];
	float color[3];
	float accentColor[3];
	float health;
	float maxHealth;
	float dimensions[2];
	float hitboxDimensions[2];
	float velocity[2];
	float shotVelocity[2];
	bool vulnerable;
	float timeLastHit = glutGet(GLUT_ELAPSED_TIME);
	float invulnerabilityTime = 600;

	bool buffed = false;
	float timeBuffed = glutGet(GLUT_ELAPSED_TIME);
	float buffTime = 7000;

	float score = 0;
	bool isAlive = true;

	void drawPlayer();
	void playerLogic();
	void takeDamage(float d);
	void setDamageable(bool damageable);
	void drawHealthbar();

	Player(float Position[2], float Color[3], float Health,
		float MaxHealth, float Dimensions[2], float HitboxDimensions[2],
		float Velocity[2], float shotVelocity[2], float accentColor[3]);
	Player();
};

