#include "Player.h"
#include <Windows.h>
#include <gl/glut.h>
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

void Player::drawPlayer()
{
	playerLogic();
	
	glLoadIdentity();
	glTranslated(position[0], position[1], 0.0);
	float width = dimensions[0];
	float height = dimensions[1];
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(color[0], color[1], color[2]);
	int quality = 40;
	float x = 0;
	float y = 0;
	float radius = width / 2;
	float twoPi = 2 * M_PI;

	glVertex2f(x, y);
	for (int i = 0; i <= quality; i++) {
		glVertex2f(
			x + (radius * cos(i * twoPi / quality)),
			y + (radius * sin(i * twoPi / quality))
		);
	}
	glEnd();

	glLoadIdentity();
	glTranslated(position[0], position[1], 0.0);
	glBegin(GL_TRIANGLES);
	glColor3f(color[0], color[1], color[2]);
	glVertex2f(radius/3, 0);
	glVertex2f(radius, 0);
	glVertex2f(radius/3, 2*radius);

	glVertex2f(-radius / 3, 0);
	glVertex2f(-radius, 0);
	glVertex2f(-radius / 3, 2 * radius);

	glEnd();

	glLoadIdentity();
	glTranslated(position[0], position[1], 0.0);
	glBegin(GL_QUADS);
	glColor3f(accentColor[0], accentColor[1], accentColor[2]);
	glVertex2f(radius * 0.6, radius * 0.6);
	glVertex2f(-radius * 0.6, -radius * 0.6);
	glVertex2f(-radius * 0.6, radius * 0.6);
	glVertex2f(radius * 0.6, -radius * 0.6);
	glEnd();

}

void Player::drawHealthbar() {
	float healthPercent = health / maxHealth;
	glLoadIdentity();
	glTranslated(80, 382, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-20 - 10, -4);
	glVertex2f(-20 - 10, 4);
	glVertex2f((-20 - 10) + (2 * (20 + 10)) * healthPercent, 4);
	glVertex2f((-20 - 10) + (2 * (20 + 10)) * healthPercent, -4);
	glEnd();
}

void Player::playerLogic()
{
	if (GetAsyncKeyState(0x41)) {
		position[0] = position[0] - velocity[0];
	}
	if (GetAsyncKeyState(0x44)) {
		position[0] = position[0] + velocity[0];
	}
	if (GetAsyncKeyState(0x53)) {
		position[1] = position[1] - velocity[1];
	}
	if (GetAsyncKeyState(0x57)) {
		position[1] = position[1] + velocity[1];
	}
	if (health <= 0) {
		isAlive = false;
	}

	if (buffed && (glutGet(GLUT_ELAPSED_TIME) - timeBuffed > buffTime)) {
		buffed = false;
		float tempColor[3] = {color[0], color[1], color[2] };
		color[0] = accentColor[0];
		color[1] = accentColor[1];
		color[2] = accentColor[2];
		accentColor[0] = tempColor[0];
		accentColor[1] = tempColor[1];
		accentColor[2] = tempColor[2];
		std::cout << "Shield dropped!\n";
	}
}

void Player::takeDamage(float d)
{
	health -= d;
}

void Player::setDamageable(bool damageable)
{
	vulnerable = damageable;
}

Player::Player(float Position[2], float Color[3], float Health,
	float MaxHealth, float Dimensions[2], float HitboxDimensions[2],
	float Velocity[2], float ShotVelocity[2], float AccentColor[3])
{
	position[0] = Position[0];
	position[1] = Position[1];
	color[0] = Color[0];
	color[1] = Color[1];
	color[2] = Color[1];
	health = Health;
	maxHealth = MaxHealth;
	dimensions[0] = Dimensions[0];
	dimensions[1] = Dimensions[1];
	hitboxDimensions[0] = HitboxDimensions[0];
	hitboxDimensions[1] = HitboxDimensions[1];
	velocity[0] = Velocity[0];
	velocity[1] = Velocity[1];
	shotVelocity[0] = ShotVelocity[0];
	shotVelocity[1] = ShotVelocity[1];
	accentColor[0] = AccentColor[0];
	accentColor[1] = AccentColor[1];
	accentColor[2] = AccentColor[2];
	vulnerable = true;
}

Player::Player()
{
	position[0] = 0;
	position[1] = 0;
	color[0] = 0.3f;
	color[1] = 0.3f;
	color[2] = 0.3f;
	accentColor[0] = 0.3f;
	accentColor[1] = 0.3f;
	accentColor[2] = 0.3f;
	health = 3;
	maxHealth = 3;
	dimensions[0] = 10;
	dimensions[1] = 10;
	hitboxDimensions[0] = 10;
	hitboxDimensions[1] = 10;
	velocity[0] = 10;
	velocity[1] = 10;
	shotVelocity[0] = 1;
	shotVelocity[1] = 1;
	vulnerable = true;
}
