#include "Chicken.h"
#include <gl/glut.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

Chicken::Chicken(float Position[2], float Velocity[2], float Color[3],
	float Health, float MaxHealth, float Dimensions[2], float HitboxDimensions[2], int Type)
{
	position[0] = Position[0];
	position[1] = Position[1];
	velocity[0] = Velocity[0];
	velocity[1] = Velocity[1];
	color[0] = Color[0];
	color[1] = Color[1];
	color[2] = Color[2];
	health = Health;
	maxHealth = MaxHealth;
	dimensions[0] = Dimensions[0];
	dimensions[1] = Dimensions[1];
	hitboxDimensions[0] = HitboxDimensions[0];
	hitboxDimensions[1] = HitboxDimensions[1];
	vulnerable = false;
	chickenType = Type;
}

Chicken::Chicken()
{
	position[0] = 0;
	position[1] = 0;
	velocity[0] = 0;
	velocity[1] = 0;
	color[0] = 0.1f;
	color[1] = 0.9f;
	color[2] = 0.5f;
	health = 3;
	maxHealth = 3;
	dimensions[0] = 15;
	dimensions[1] = 15;
	hitboxDimensions[0] = 15;
	hitboxDimensions[1] = 15;
	vulnerable = false;
}

void Chicken::drawChicken()
{
	chickenLogic();
	float width = dimensions[0];
	float height = dimensions[1];
	glLoadIdentity();
	glTranslated(position[0], position[1], 0.0);
	glColor3f(color[0], color[1], color[2]);
	
	if (chickenType == 0 || chickenType == 2) {
		glBegin(GL_POLYGON);
		glVertex2f(width, height);
		glVertex2f(-width, height);
		glVertex2f(-width, -height);
		glVertex2f(width, -height);
		glEnd();
	}

	else if(chickenType == 1) {
		glColor3f(1, 1, 1);
		glBegin(GL_POLYGON);
		glVertex2f(-width * 0.8, 0);
		glVertex2f(-width, 0.75 * height);
		glVertex2f(width, 0.75 * height);
		glVertex2f(width * 0.8, 0);
		glEnd();

		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_TRIANGLES);
		glVertex2f(-width, 0.75 * height);
		glVertex2f(-width + 0.4 * width, 0.75 * height);
		glVertex2f(-width + 0.2 * width, 1.10 * height);

		glVertex2f(-width + 0.4 * width, 0.75 * height);
		glVertex2f(-width + 0.8 * width, 0.75 * height);
		glVertex2f(-width + 0.6 * width, 1.05 * height);

		glVertex2f(-width + 0.8 * width, 0.75 * height);
		glVertex2f(-width + 1.2 * width, 0.75 * height);
		glVertex2f(-width + 1.0 * width, 1.05 * height);

		glVertex2f(-width + 1.2 * width, 0.75 * height);
		glVertex2f(-width + 1.6 * width, 0.75 * height);
		glVertex2f(-width + 1.4 * width, 1.05 * height);

		glVertex2f(-width + 1.6 * width, 0.75 * height);
		glVertex2f(-width + 2.0 * width, 0.75 * height);
		glVertex2f(-width + 1.8 * width, 1.10 * height);
		
		glColor3f(255.0f/255.0f, 227.0f/255.0f, 82/255.0f);
		glVertex2f(-width + 0.4 * width, 0);
		glVertex2f(-width + 1.6 * width, 0);
		glVertex2f(-width + 1.0 * width, -0.75 * height);
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLE_FAN);
		int quality = 40;
		float x = -width/2;
		float y = 0.375 * height;
		float radius = width / 5;
		float twoPi = 2 * M_PI;

		glVertex2f(x, y);
		for (int i = 0; i <= quality; i++) {
			glVertex2f(
				x + (radius * cos(i * twoPi / quality)),
				y + (radius * sin(i * twoPi / quality))
			);
		}
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLE_FAN);
		quality = 40;
		x = width / 2;
		y = 0.375 * height;
		radius = width / 5;
		twoPi = 2 * M_PI;

		glVertex2f(x, y);
		for (int i = 0; i <= quality; i++) {
			glVertex2f(
				x + (radius * cos(i * twoPi / quality)),
				y + (radius * sin(i * twoPi / quality))
			);
		}
		glEnd();

	}
	
}

void Chicken::chickenLogic()
{
	//Reflection logic
	if (position[0] >= 400) {
		velocity[0] = -1 * velocity[0];
	}
	else if (position[0] <= 0) {
		velocity[0] = -1 * velocity[0];
	}

	//Type specific logic
	if (chickenType == 0 || chickenType == 2) {
		position[0] += velocity[0];
		position[1] += velocity[1];
	}
	else if (chickenType == 1) {
		position[0] += velocity[0];
	}
	
	
}

void Chicken::takeDamage(float d)
{
	health -= d;
}

void Chicken::setDamageable(bool damageable)
{
	vulnerable = damageable;
}

void Chicken::drawHealthbar() {
	glLoadIdentity();
	glTranslated(position[0], position[1] + dimensions[1] + 12, 0.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2f(position[0] - 10, 5);
	glVertex2f(-(position[0] - 10), 5);
	glVertex2f(-(position[0] - 10), -5);
	glVertex2f((position[0] - 10), -5);
	glEnd();
}