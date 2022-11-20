#include "Projectile.h"

Projectile::Projectile(float Position[2], float Velocity[2], float Color[3],
	float Life, int SourceID, float Dimensions[2], float HitboxDimensions[2])
{
	position[0] = Position[0];
	position[1] = Position[1];
	velocity[0] = Velocity[0];
	velocity[1] = Velocity[1];
	color[0] = Color[0];
	color[1] = Color[1];
	color[2] = Color[2];
	life = Life;
	sourceID = SourceID;
	dimensions[0] = Dimensions[0];
	dimensions[1] = Dimensions[1];
	hitboxDimensions[0] = HitboxDimensions[0];
	hitboxDimensions[1] = HitboxDimensions[1];
}



void Projectile::projectileLogic()
{
	position[0] += velocity[0];
	position[1] += velocity[1];
	life -= decayRate;
}

Projectile::Projectile()
{
	position[0] = 0;
	position[1] = 0;
	velocity[0] = 1;
	velocity[1] = 1;
	color[0] = 0.5f;
	color[1] = 0.5f;
	color[2] = 0.5f;
	life = 600;
	sourceID = -1;
	dimensions[0] = 10;
	dimensions[1] = 10;
	hitboxDimensions[0] = 10;
	hitboxDimensions[1] = 10;

}
