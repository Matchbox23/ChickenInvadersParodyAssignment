#include "PowerUp.h"
#include <gl/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

PowerUp::PowerUp(float Position[2], int Type) {
	position[0] = Position[0];
	position[1] = Position[1];
	type = Type;
	timeSpawned = glutGet(GLUT_ELAPSED_TIME);
}

void PowerUp::drawPowerUp()
{
	glLoadIdentity();
	glTranslated(position[0], position[1], 0.0);
	glBegin(GL_TRIANGLE_FAN);
	switch (type) {
	case 1:
		glColor3f(91.0/255.0, 255.0/255.0, 174.0/255.0);
	}
	int quality = 40;
	float x = 0;
	float y = 0;
	float twoPi = 2 * M_PI;

	glVertex2f(x, y);
	for (int i = 0; i <= quality; i++) {
		glVertex2f(
			x + (radius * cos(i * twoPi / quality)),
			y + (radius * sin(i * twoPi / quality))
		);
	}
	glEnd();
}