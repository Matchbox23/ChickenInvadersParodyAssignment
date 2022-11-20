#pragma once
class PowerUp
{
public:
	float position[2];
	int type = 0;
	float radius = 10;
	float timeSpawned;
	bool alive = true;
	
	PowerUp(float Position[2], int type);
	PowerUp();

	void drawPowerUp();
};

