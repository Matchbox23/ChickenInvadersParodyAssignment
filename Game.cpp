#include "Game.h"
#include <iostream>
#include <gl/glut.h>
#include <string>
#include <random>
using namespace std;

Game::Game(Player p, int GameMode)
{
    player = p;
    gameMode = GameMode;
}

Game::Game() {
    player = Player();
}

void Game::setPlayer(Player p)
{
	player = p;
}

void Game::createProjectile(float position[2], float velocity[2], float color[3], float life, int sourceID, float dimensions[2], float hitboxDimensions[2])
{
    if (sourceID == 0) {
        if (glutGet(GLUT_ELAPSED_TIME) - lastShotTime > shotCD) {
            if (projectiles.size() < maxProjectiles) {
                projectiles.push(Projectile(position, velocity, color, life, sourceID, dimensions, hitboxDimensions));
                lastShotTime = glutGet(GLUT_ELAPSED_TIME);
                cout << "Fired!\n";
            }
            else {
            }
        }
        else {
            cout << "Too hot!\n";
        }
    }
    else if (sourceID == 1) {
        projectiles.push(Projectile(position, velocity, color, life, sourceID, dimensions, hitboxDimensions));
    }
	
}

void Game::drawProjectiles()
{
    while (!projectiles.empty()) {
        projectiles.top().projectileLogic();
        Projectile temp = projectiles.top();
        projectiles.pop();

        glLoadIdentity();

        glColor3f(temp.color[0], temp.color[1], temp.color[2]);
        glBegin(GL_POLYGON);
        float x = temp.position[0];
        float y = temp.position[1];
        float width = temp.dimensions[0];
        float height = temp.dimensions[1];
        glVertex2f(x - width, y - height);
        glVertex2f(x - width, y + height);
        glVertex2f(x + width, y + height);
        glVertex2f(x + width, y - height);
        glEnd();
        tempProjectiles.push(temp);
    }

    while (!tempProjectiles.empty()) {
        Projectile temp = tempProjectiles.top();
        tempProjectiles.pop();

        if (temp.life > 0) {
            projectiles.push(temp);
        }
        else {
        }
    }
}

void Game::createChicken(float position[2], float velocity[2], float color[3], float health, float maxHealth, float dimensions[2], float hitboxDimensions[2], int Type)
{
    if (chickenBucket.size() < maxChickens && Type != 2) {
        chickenBucket.push(Chicken(position, velocity, color, health, maxHealth, dimensions, hitboxDimensions, Type));
        totalSpawnedChickens++;
        if (totalSpawnedChickens >= 35) {
            chickenTimer = 30;
        }
        else {
            chickenTimer = 75 - totalSpawnedChickens;
        }
    }

    if (chickenBucket.size() < maxChickens && Type == 2) {
        chickenBucket.push(Chicken(position, velocity, color, health, maxHealth, dimensions, hitboxDimensions, Type));
        totalSpawnedChickens++;
        starTimer = ((bossKills + 1) * 10)/(bossKills + 1);
    }
}

void Game::createPowerUp(float position[2]) {
    if (powerUps.size() < maxPowerUps) {
        powerUps.push(PowerUp(position, 1));
    }
}

void Game::drawPowerUps() {
    while (!powerUps.empty()) {
        PowerUp temp = powerUps.top();
        powerUps.pop();
        temp.drawPowerUp();
        tempPowerUps.push(temp);
    }
    while (!tempPowerUps.empty()) {
        PowerUp temp = tempPowerUps.top();
        tempPowerUps.pop();
        if (temp.alive) {
            powerUps.push(temp);
        }
    }
}

void Game::drawChickens()
{
    while (!chickenBucket.empty()) {
        chickenBucket.top().chickenLogic();
        Chicken temp = chickenBucket.top();
        chickenBucket.pop();

        if (temp.chickenType == 1) {
            if (glutGet(GLUT_ELAPSED_TIME) - temp.timeSinceLastShot > (temp.shotCD/(bossKills + 1))) {
                float shooter[2] = { temp.position[0], temp.position[1] - temp.dimensions[1] - 10 };
                float multipliedShotVelocity[2] = { temp.shotVelocity[0], (temp.shotVelocity[1] * (bossKills + 1)) };
                createProjectile(shooter, multipliedShotVelocity, temp.shotColor,
                    5000, 1, temp.shotSize, temp.shotSizeHitbox);
                temp.timeSinceLastShot = glutGet(GLUT_ELAPSED_TIME);
            }
        }

        float healthPercent = temp.health / temp.maxHealth;

        temp.drawChicken();

        //Drawing Chicken Healthbar
        if (temp.chickenType != 2) {
            glLoadIdentity();
            glTranslated(temp.position[0], temp.position[1] + temp.dimensions[1] + 10, 0.0);
            glColor3f(1.0f, 0.0f, 0.0f);
            glBegin(GL_QUADS);
            glVertex2f(-temp.dimensions[0] - 10, -5);
            glVertex2f(-temp.dimensions[0] - 10, 5);
            glVertex2f((-temp.dimensions[0] - 10) + (2 * (temp.dimensions[0] + 10)) * healthPercent, 5);
            glVertex2f((-temp.dimensions[0] - 10) + (2 * (temp.dimensions[0] + 10)) * healthPercent, -5);
            glEnd();
        }
        tempBucket.push(temp);
    }

    while (!tempBucket.empty()) {
        Chicken temp = tempBucket.top();
        tempBucket.pop();

        if (temp.health > 0 && temp.position[1] > -10) {
            chickenBucket.push(temp);
        }
        else if (temp.health <= 0 && temp.chickenType == 1) {
            player.score += 100;
        }
        else if (temp.position[1] <= 0) {
        }
    }

    chickenTimer--;
    starTimer--;
}

void Game::drawStartScreen()
{
    std::string text;
    text = "Welcome to Invaders! Used 'wasd' to move and 'l' to shoot. Shoot to start!";
    drawText(text.data(), text.size(), 0, 0);
    glEnd();
}

void Game::drawDeathScreen()
{
    std::string text;
    text = "You died! Shoot to restart!";
    drawText(text.data(), text.size(), 0, -80);
    glEnd();
}

void Game::drawPlayerStats()
{
    std::string text;
    std::string text2;
    std::string text3;
    text = "Score: " + std::to_string((int) player.score);
    text2 = "Health: " + std::to_string((int) player.health);
    text3 = "FPS: " + std::to_string(framerate);
    drawText(text2.data(), text2.size(), 0, 0);
    player.drawHealthbar();
    drawText(text.data(), text.size(), 0, -20);
    drawText(text3.data(), text3.size(), 0, -40);
    glEnd();
}

void Game::drawText(const char* text, int length, int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    double* matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(30 + x, 570 + y);
    glColor3f(0.0f, 1.0f, 0.0f);
    for (int i = 0; i < length; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

void Game::spawnChickens() {
    if (gameMode == 0) {
        if(chickenTimer <= 0 && chickenBucket.size() < maxChickens) {
            float position[2] = { rand() % 400, 400 };
            float velocity[2] = { 0, -0.5f };
            float color[3] = { 0.6f, 0.5f, 0.3f };
            float health = 3;
            float maxHealth = 3;
            float dimensions[2] = { 10, 10 };
            float hitboxDimensions[2] = { 10, 10 };
            createChicken(position, velocity, color, health, maxHealth,
                dimensions, hitboxDimensions, 0);
        }
    }
    else if (gameMode == 1) {
        if (!bossAlive) {
            if (glutGet(GLUT_ELAPSED_TIME) - lastBossKillTime > roundWaitTime) {
                spawnChickenBoss();
                bossAlive = true;
            }
        }
        if (starTimer <= 0 && chickenBucket.size() < (maxChickens - 1)) {
            float position[2] = { rand() % 400, 400 };
            float velocity[2] = { 0, -2.0f * (bossKills + 1)};
            float color[3] = { 1, 1, 1 };
            float health = 3;
            float maxHealth = 3;
            float dimensions[2] = { 2, 2 };
            float hitboxDimensions[2] = { 0, 0 };
            createChicken(position, velocity, color, health, maxHealth,
                dimensions, hitboxDimensions, 2);
        }
    }
}

void Game::spawnChickenBoss() {
    float position[2] = { 200, 320 };
    float velocity[2] = { 2 * (bossKills + 1), 0};
    float color[3] = { static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ,
        static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 
        static_cast <float> (rand()) / static_cast <float> (RAND_MAX)};
    float health = 10;
    float maxHealth = 10;
    float dimensions[2] = { 50, 50 };
    float hitboxDimensions[2] = { 30, 30 };
    createChicken(position, velocity, color, health, maxHealth,
        dimensions, hitboxDimensions, 1);
}

void Game::spawnPowerUps() {
    if (powerUps.empty() && (glutGet(GLUT_ELAPSED_TIME) - timeSinceLastPowerUpPickUp > powerUpCD)) {
        float position[2] = { 10 + rand() % 380, 10 + rand() % 275};
        createPowerUp(position);
    }
    

}

void Game::checkForDeath() {
    if (!player.isAlive) {
        currentScene = 2;
    }
}

void Game::checkCollisions() {
    while (!chickenBucket.empty()) {
        Chicken tempChicken = chickenBucket.top();
        chickenBucket.pop();
        if (tempChicken.vulnerable == false) {
            if (glutGet(GLUT_ELAPSED_TIME) - tempChicken.timeLastHit > tempChicken.invulnerabilityTime) {
                tempChicken.vulnerable = true;
            }
        }

        if (player.vulnerable == false) {
            if (glutGet(GLUT_ELAPSED_TIME) - player.timeLastHit > player.invulnerabilityTime) {
                player.vulnerable = true;
            }
        }
        else if(!player.buffed) {
            while (!projectiles.empty()) {
                Projectile tempProjectile = projectiles.top();
                projectiles.pop();
                bool laserAliveFlag = true;

                float projX = tempProjectile.position[0];
                float projY = tempProjectile.position[1];
                float projHBX = tempProjectile.hitboxDimensions[0];
                float projHBY = tempProjectile.hitboxDimensions[1];
                float chiX = player.position[0];
                float chiY = player.position[1];
                float chiHBX = player.hitboxDimensions[0];
                float chiHBY = player.hitboxDimensions[1];

                if (projX + projHBX > chiX - chiHBX && projX - projHBX < chiX + chiHBX) {
                    if (projY + projHBY > chiY - chiHBY && projY - projHBY < chiY + chiHBY) {
                        player.takeDamage(1);
                        player.vulnerable = false;
                        player.timeLastHit = glutGet(GLUT_ELAPSED_TIME);
                        cout << "Player zapped! \n";
                        laserAliveFlag = false;
                    }
                }
                if (laserAliveFlag) {
                    tempProjectiles.push(tempProjectile);
                }
            }
            while (!tempProjectiles.empty()) {
                Projectile temp = tempProjectiles.top();
                tempProjectiles.pop();

                if (temp.life > 0) {
                    projectiles.push(temp);
                }
                else {
                    cout << "Laser fizzled! \n";
                }
            }
        }

        if (tempChicken.vulnerable == true) {

            while (!projectiles.empty()) {
                Projectile tempProjectile = projectiles.top();
                projectiles.pop();
                bool laserAliveFlag = true;

                float projX = tempProjectile.position[0];
                float projY = tempProjectile.position[1];
                float projHBX = tempProjectile.hitboxDimensions[0];
                float projHBY = tempProjectile.hitboxDimensions[1];
                float chiX = tempChicken.position[0];
                float chiY = tempChicken.position[1];
                float chiHBX = tempChicken.hitboxDimensions[0];
                float chiHBY = tempChicken.hitboxDimensions[1];

                if (projX + projHBX > chiX - chiHBX && projX - projHBX < chiX + chiHBX) {
                    if (projY + projHBY > chiY - chiHBY && projY - projHBY < chiY + chiHBY) {
                        tempChicken.takeDamage(1);
                        tempChicken.vulnerable = false;
                        tempChicken.timeLastHit = glutGet(GLUT_ELAPSED_TIME);
                        cout << "Chicken zapped! \n";
                        laserAliveFlag = false;
                    }
                }
                if(laserAliveFlag){
                    tempProjectiles.push(tempProjectile);
                }
            }       
            while (!tempProjectiles.empty()) {
                Projectile temp = tempProjectiles.top();
                tempProjectiles.pop();

                if (temp.life > 0) {
                    projectiles.push(temp);
                }
                else {
                    cout << "Laser fizzled! \n";
                }
            }
        }

        if (tempChicken.vulnerable && player.vulnerable && !player.buffed) {
            float projX = player.position[0];
            float projY = player.position[1];
            float projHBX = player.hitboxDimensions[0];
            float projHBY = player.hitboxDimensions[1];
            float chiX = tempChicken.position[0];
            float chiY = tempChicken.position[1];
            float chiHBX = tempChicken.hitboxDimensions[0];
            float chiHBY = tempChicken.hitboxDimensions[1];

            if (projX + projHBX > chiX - chiHBX && projX - projHBX < chiX + chiHBX) {
                if (projY + projHBY > chiY - chiHBY && projY - projHBY < chiY + chiHBY) {
                    if (tempChicken.chickenType == 0) {
                        player.takeDamage(1);
                    }
                    if (tempChicken.chickenType == 1) {
                        player.takeDamage(5);
                    }
                    player.vulnerable = false;
                    player.timeLastHit = glutGet(GLUT_ELAPSED_TIME);
                    cout << "Player whacked! \n";
                }
            }
        }

        tempBucket.push(tempChicken);
    }
    while (!tempBucket.empty()) {
        Chicken temp = tempBucket.top();
        tempBucket.pop();

        if (temp.health > 0 && temp.position[1] > -10) {
            chickenBucket.push(temp);
        }
        else {
            if (temp.chickenType == 0) {
                cout << "Killed a Chicken! \n";
                player.score += 100;
            }
            if (temp.chickenType == 1) {
                cout << "Killed a Boss Chicken! \n";
                player.score += 300;
                lastBossKillTime = glutGet(GLUT_ELAPSED_TIME);
                bossKills++;
                bossAlive = false;
            }
        }
    }
    while (!powerUps.empty()) {
        PowerUp temp = powerUps.top();
        powerUps.pop();

        float playerX = player.position[0];
        float playerY = player.position[1];
        float playerHBX = player.hitboxDimensions[0];
        float playerHBY = player.hitboxDimensions[1];
        float powerUpX = temp.position[0];
        float powerUpY = temp.position[1];
        float powerUpR = temp.radius;

        if (playerX + playerHBX > powerUpX - powerUpR && playerX - playerHBX < powerUpX + powerUpR) {
            if (playerY + playerHBY > powerUpY - powerUpR && playerY - playerHBY < powerUpY + powerUpR) {
                player.buffed = true;
                player.timeBuffed = glutGet(GLUT_ELAPSED_TIME);
                timeSinceLastPowerUpPickUp = glutGet(GLUT_ELAPSED_TIME);
                float tempColor[3] = { player.color[0], player.color[1], player.color[2] };
                player.color[0] = player.accentColor[0];
                player.color[1] = player.accentColor[1];
                player.color[2] = player.accentColor[2];
                player.accentColor[0] = tempColor[0];
                player.accentColor[1] = tempColor[1];
                player.accentColor[2] = tempColor[2];
                cout << "Immune to bullets! \n";
                temp.alive = false;
            }
        }
        tempPowerUps.push(temp);
    }
    while (!tempPowerUps.empty()) {
        PowerUp temp = tempPowerUps.top();
        tempPowerUps.pop();

        if (temp.alive) {
            powerUps.push(temp);
        }
    }
}

