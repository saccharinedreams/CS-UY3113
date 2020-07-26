#include "Level3.h"
#define LEVEL3_WIDTH 14
#define LEVEL3_HEIGHT 8

#define ENEMY_COUNT 3

unsigned int level3_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
 3, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3
};

void Level3::Initialize(int livesLeft) {

    state.nextScene = -1;
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 4, 1);
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
    GLuint enemyTextureID = Util::LoadTexture("flying bug.png");
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(10.0f, -4.75f, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = GLIDER;
    state.enemies[0].acceleration = glm::vec3(0, -0.2f, 0);
    state.enemies[0].aiState = IDLE;
    state.enemies[0].isActive = true;

    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(7.0f, -1.0f, 0);
    state.enemies[1].speed = 1;
    state.enemies[1].aiType = GLIDER;
    state.enemies[1].acceleration = glm::vec3(0, -0.2f, 0);
    state.enemies[1].aiState = IDLE;
    state.enemies[1].isActive = true;

    state.enemies[2].entityType = ENEMY;
    state.enemies[2].textureID = enemyTextureID;
    state.enemies[2].position = glm::vec3(10.0f, -3.0f, 0);
    state.enemies[2].speed = 1;
    state.enemies[2].aiType = GLIDER;
    state.enemies[2].acceleration = glm::vec3(0, -0.2f, 0);
    state.enemies[2].aiState = IDLE;
    state.enemies[2].isActive = true;
}

void Level3::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, ENEMY_COUNT, state.map);
    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, ENEMY_COUNT, state.map);
    }
    if (state.player->position.x >= 12) state.won = true;
}
void Level3::Render(ShaderProgram* program) {
    state.map->Render(program);
    for (int i = 0; i < ENEMY_COUNT; i++) state.enemies[i].Render(program);
    state.player->Render(program);
}