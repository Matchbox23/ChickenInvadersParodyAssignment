#pragma once
class Projectile
{
public:
	float position[2];
	float velocity[2];
	float color[3];
	float life;
	int sourceID;
	float dimensions[2];
	float hitboxDimensions[2];
	const float decayRate = 20;

	Projectile(float Position[2], float Velocity[2], float Color[3], float Life,
		int SourceID, float dimensions[2], float hitboxDimensions[2]);
	void projectileLogic();
	Projectile();
};

