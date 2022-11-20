#pragma once
#include <gl/glut.h>
class Chicken
{
public:
	float position[2];
	float velocity[2];
	float color[3];
	float health;
	float maxHealth;
	float dimensions[2];
	float hitboxDimensions[2];
	int chickenType;

	float shotVelocity[2] = { 0, -7 };
	float shotColor[3] = { 0.9f, 0.1f, 0.0f };
	float shotSize[2] = { 3, 10 };
	float shotSizeHitbox[2] = { 3, 10 };

	bool vulnerable;
	float timeLastHit = glutGet(GLUT_ELAPSED_TIME);
	float invulnerabilityTime = 200;

	float timeSinceLastShot = glutGet(GLUT_ELAPSED_TIME);
	float shotCD = 200;

	void drawChicken();
	void chickenLogic();
	void takeDamage(float d);
	void setDamageable(bool damageable);
	void drawHealthbar();
	Chicken(float Position[2], float Velocity[2], float Color[3],
		float health, float MaxHealth,
		float Dimensions[2], float HitboxDimensions[2], int Type);
	Chicken();
};

