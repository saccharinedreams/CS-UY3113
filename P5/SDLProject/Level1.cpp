#include "Level1.h"
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8

#define ENEMY_COUNT 1   

unsigned int level1_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

void Level1::Initialize(int livesLeft) {

    state.nextScene = -1;
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 4, 1);
    // Initialize Game Objects
    // Initialize Player    
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->lives = livesLeft;
    state.player->position = glm::vec3(2, -3, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 3.5f;
    state.player->height = 0.8f;
    state.player->width = 0.7f;
    state.player->textureID = Util::LoadTexture("spaceship.png");

    state.enemies = new Entity[ENEMY_COUNT];
    state.enemies[0].entityType = ENEMY;
    GLuint enemyTextureID = Util::LoadTexture("flying bug.png");
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(10.0f, -4.75f, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = GLIDER;
    state.enemies[0].acceleration = glm::vec3(0, -0.2f, 0);
    state.enemies[0].aiState = IDLE;
    state.enemies[0].isActive = true;
}

void Level1::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, ENEMY_COUNT, state.map);
    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, ENEMY_COUNT, state.map);
    }
    if (state.player->position.x >= 12) state.nextScene = 2;
}
void Level1::Render(ShaderProgram* program) {
    state.map->Render(program);
    for (int i = 0; i < ENEMY_COUNT; i++) state.enemies[i].Render(program);
    state.player->Render(program);
}
