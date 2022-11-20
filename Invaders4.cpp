#include <gl/glut.h>
#include <stack>
#include "Projectile.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <time.h>

#define FPS 60

//Written by Yousef Korayem 49-5052

//Player data
float position[2] = { 200, 50 };
float color[3] = { 1, 1, 1 };
float accentColor[3] = { 0/255, 77/255, 255/255 };
float dimensions[2] = { 30, 30 };
float hitboxDimensions[2] = { 15, 15 };
float velocity[2] = { 6,6 };
float shotVelocity[2] = { 0, 5 };
Player p1(position, color, 10, 10, dimensions, hitboxDimensions, velocity, shotVelocity, accentColor);

//Game setup
Game game(p1, 1);
float bgColor[3] = { 0, 0, 0 };

//Unused
float chickenVelocity[2] = { 0, 0 };
float chickenColor[3] = { 0.5f, 1.0f, 0.75f };
float chickenSize[2] = { 25, 25 };
float chickenPosition[2] = { 75, 125 };



void Display() {
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);

    if (game.currentScene == 0) {
        game.drawStartScreen();
    }
    if (game.currentScene == 1) {
        game.spawnChickens();
        game.spawnPowerUps();
        game.player.drawPlayer();
        game.drawPowerUps();
        game.drawProjectiles();
        game.drawChickens();
        glColor3f(0.0f, 1.0f, 0.0f);
        game.drawPlayerStats();
        game.checkCollisions();
        game.checkForDeath();
    }
    if (game.currentScene == 2) {
        game.drawPlayerStats();
        game.drawDeathScreen();
    }
    glutSwapBuffers();
    game.frame_count++;
    game.final_time = time(NULL);
    if (game.final_time - game.initial_time > 0) {
        game.framerate = game.frame_count / (game.final_time - game.initial_time);
        game.frame_count = 0;
        game.initial_time = game.final_time;
    }
    glFlush();
}

void initOpenGl()
{
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1); //Background Color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 0, 400);
    glMatrixMode(GL_MODELVIEW);
}

void key(unsigned char key, int x, int y) {
    float playerShotColor[3] = { 255/255, 255/255, 0 };
    float playerShotSize[2] = { 2, 10 };
    float playerShotHitbox[2] = { 2, 10 };
    if (key == 'l') {
        if (game.currentScene == 0 || game.currentScene == 2) {
            game.player.score = 0;
            game.player.health = 10;
            game.player.position[0] = 200;
            game.player.position[1] = 10;
            game.player.isAlive = true;
            game.bossKills = 0;
            game.lastBossKillTime = glutGet(GLUT_ELAPSED_TIME);
            game.lastShotTime = glutGet(GLUT_ELAPSED_TIME);
            game.timeSinceLastPowerUpPickUp = glutGet(GLUT_ELAPSED_TIME);
            while (!game.projectiles.empty()) {
                game.projectiles.pop();
            }
            while (!game.tempProjectiles.empty()) {
                game.tempProjectiles.pop();
            }
            while (!game.chickenBucket.empty()) {
                game.chickenBucket.pop();
            }
            while (!game.tempBucket.empty()) {
                game.tempBucket.pop();
            }
            game.chickenTimer = 0;
            game.currentScene = 1;
        }
        else {
            float shooter[2] = { game.player.position[0], game.player.position[1] + 25 };
            game.createProjectile(shooter, game.player.shotVelocity,
                playerShotColor, 9000, 0, playerShotSize, playerShotHitbox);
        }
    }
}

void idle(int) {
    glutTimerFunc(750 / FPS, idle, 0);
    glutPostRedisplay();
}

//Written by Yousef Korayem 49-5052

void main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Invaders");
    initOpenGl();
    glutDisplayFunc(Display);
    glutKeyboardFunc(key);
    glutTimerFunc(750 / FPS, idle, 0);
    glutMainLoop();
}