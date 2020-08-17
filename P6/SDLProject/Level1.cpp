#include "Level1.h"
#define LEVEL1_WIDTH 20
#define LEVEL1_HEIGHT 21

#define ENEMY_COUNT 42
unsigned int level1_data[] =
{
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
 3, 0, 0, 0, 0, 3, 0, 0, 3, 0, 3, 0, 3, 0, 3, 3, 3, 3, 3, 3,
 3, 0, 3, 0, 3, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 0, 3, 0, 0, 0, 3, 3, 0, 0, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3,
 3, 0, 3, 3, 3, 0, 3, 0, 0, 3, 3, 0, 3, 0, 3, 3, 3, 3, 0, 3,
 3, 3, 3, 3, 3, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3,
 3, 0, 0, 3, 0, 0, 3, 0, 3, 0, 0, 3, 0, 3, 3, 3, 0, 0, 0, 3,
 3, 0, 3, 3, 0, 3, 3, 0, 3, 0, 3, 3, 0, 0, 0, 3, 3, 3, 0, 3,
 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 3, 0, 3, 0, 0, 0, 0, 0, 3,
 3, 3, 3, 0, 3, 3, 3, 0, 3, 0, 3, 0, 0, 3, 3, 3, 3, 3, 0, 3,
 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, 3, 0, 3, 3, 0, 3, 3, 0, 0, 3,
 3, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 3, 0, 0, 3, 3, 0, 3, 3,
 3, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 3, 3, 3, 0, 3, 0, 3, 0, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3,
 3, 3, 0, 3, 0, 0, 0, 0, 0, 3, 0, 3, 3, 3, 0, 3, 0, 0, 0, 3,
 3, 3, 0, 3, 3, 3, 3, 3, 0, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0, 3,
 3, 0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 3, 3, 3, 0, 0, 0, 3, 0, 3,
 3, 0, 3, 3, 3, 0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3,
 3, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 3, 3, 3, 0, 3, 3, 3,
 3, 0, 3, 0, 3, 3, 3, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3
};

void Level1::Initialize() {

    //state.nextScene = -1;
    GLuint mapTextureID = Util::LoadTexture("laser_tileset.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 2.0f, 4, 1);
    // Initialize Game Objects
    // Initialize Player    
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(2, -3, 0);
    state.player->movement = glm::vec3(0);
    state.player->speed = 9.0f;
    state.player->height = 0.8f;
    state.player->width = 0.7f;
    state.player->textureID = Util::LoadTexture("player.png");

    
    state.enemies = new Entity[ENEMY_COUNT];
    GLuint monsterTextureID = Util::LoadTexture("monster.png");
    GLuint guardTextureID = Util::LoadTexture("guard.png");
    GLuint patrollerTextureID = Util::LoadTexture("patroller.png");
    GLuint droneTextureID = Util::LoadTexture("drone.png");

    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemies[i].entityType = ENEMY;

    }
   
    state.enemies[0].textureID = monsterTextureID;
    state.enemies[0].position = glm::vec3(2.0f, 3.0f, 0);
    state.enemies[0].speed = 2;
    state.enemies[0].aiType = FOLLOWER;
    state.enemies[0].aiState = FOLLOW;
    state.enemies[0].isActive = true;

    state.enemies[1].textureID = guardTextureID;
    state.enemies[1].position = glm::vec3(2.0f, -7.0f, 0);
    state.enemies[1].spawn = glm::vec3(2.0f, -7.0f, 0);
    state.enemies[1].speed = 0.7;
    state.enemies[1].aiType = GUARD;
    state.enemies[1].aiState = IDLE;
    state.enemies[1].isActive = true;

    state.enemies[2].textureID = patrollerTextureID;
    state.enemies[2].position = glm::vec3(6.0f, -6.0f, 0);
    state.enemies[2].spawn = glm::vec3(6.0f, -6.0f, 0);
    state.enemies[2].speed = 0.8;
    state.enemies[2].aiType = VERTICAL_PATROLLER;
    state.enemies[2].aiState = PATROLY;
    state.enemies[2].isActive = true;

    state.enemies[3].textureID = patrollerTextureID;
    state.enemies[3].position = glm::vec3(6.0f, -10.0f, 0);
    state.enemies[3].spawn = glm::vec3(6.0f, -10.0f, 0);
    state.enemies[3].speed = 0.8;
    state.enemies[3].aiType = HORIZONTAL_PATROLLER;
    state.enemies[3].aiState = PATROLX;
    state.enemies[3].isActive = true;

    state.enemies[4].textureID = droneTextureID;
    state.enemies[4].position = glm::vec3(6.0f, -4.0f, 0);
    state.enemies[4].spawn = glm::vec3(6.0f, -4.0f, 0);
    state.enemies[4].speed = 0.8;
    state.enemies[4].aiType = HORIZONTAL_PATROLLER;
    state.enemies[4].aiState = PATROLX;
    state.enemies[4].isActive = true;

    state.enemies[5].textureID = droneTextureID;
    state.enemies[5].position = glm::vec3(12.0f, -10.0f, 0);
    state.enemies[5].spawn = glm::vec3(12.0f, -10.0f, 0);
    state.enemies[5].speed = 1.9;
    state.enemies[5].aiType = VERTICAL_PATROLLER;
    state.enemies[5].aiState = PATROLY;
    state.enemies[5].isActive = true;

    state.enemies[6].textureID = guardTextureID;
    state.enemies[6].position = glm::vec3(9.0f, -2.0f, 0);
    state.enemies[6].spawn = glm::vec3(9.0f, -2.0f, 0);
    state.enemies[6].speed = 0.8;
    state.enemies[6].aiType = GUARD;
    state.enemies[6].aiState = IDLE;
    state.enemies[6].isActive = true;

    state.enemies[7].textureID = guardTextureID;
    state.enemies[7].position = glm::vec3(12.0f, -1.0f, 0);
    state.enemies[7].spawn = glm::vec3(12.0f, -1.0f, 0);
    state.enemies[7].speed = 0.8;
    state.enemies[7].aiType = GUARD;
    state.enemies[7].aiState = IDLE;
    state.enemies[7].isActive = true;

    state.enemies[8].textureID = patrollerTextureID;
    state.enemies[8].position = glm::vec3(15.0f, -3.0f, 0);
    state.enemies[8].spawn = glm::vec3(15.0f, -3.0f, 0);
    state.enemies[8].speed = 0.8;
    state.enemies[8].aiType = HORIZONTAL_PATROLLER;
    state.enemies[8].aiState = PATROLX;
    state.enemies[8].isActive = true;

    state.enemies[9].textureID = guardTextureID;
    state.enemies[9].position = glm::vec3(20.0f, -10.0f, 0);
    state.enemies[9].spawn = glm::vec3(20.0f, -10.0f, 0);
    state.enemies[9].speed = 0.8;
    state.enemies[9].aiType = GUARD;
    state.enemies[9].aiState = IDLE;
    state.enemies[9].isActive = true;

    state.enemies[10].textureID = patrollerTextureID;
    state.enemies[10].position = glm::vec3(20.0f, -14.0f, 0);
    state.enemies[10].spawn = glm::vec3(20.0f, -14.0f, 0);
    state.enemies[10].speed = 0.8;
    state.enemies[10].aiType = VERTICAL_PATROLLER;
    state.enemies[10].aiState = PATROLY;
    state.enemies[10].isActive = true;

    state.enemies[11].textureID = patrollerTextureID;
    state.enemies[11].position = glm::vec3(24.0f, -11.0f, 0);
    state.enemies[11].spawn = glm::vec3(24.0f, -11.0f, 0);
    state.enemies[11].speed = 0.8;
    state.enemies[11].aiType = VERTICAL_PATROLLER;
    state.enemies[11].aiState = PATROLY;
    state.enemies[11].isActive = true;

    state.enemies[12].textureID = patrollerTextureID;
    state.enemies[12].position = glm::vec3(20, -3, 0);
    state.enemies[12].spawn = glm::vec3(20, -3, 0);
    state.enemies[12].speed = 0.8;
    state.enemies[12].aiType = HORIZONTAL_PATROLLER;
    state.enemies[12].aiState = PATROLX;
    state.enemies[12].isActive = true;

    state.enemies[13].textureID = patrollerTextureID;
    state.enemies[13].position = glm::vec3(22, -1, 0);
    state.enemies[13].spawn = glm::vec3(22, -1, 0);
    state.enemies[13].speed = 3.0;
    state.enemies[13].aiType = VERTICAL_PATROLLER;
    state.enemies[13].aiState = PATROLY;
    state.enemies[13].isActive = true;

    state.enemies[14].textureID = droneTextureID;
    state.enemies[14].position = glm::vec3(26, -1, 0);
    state.enemies[14].spawn = glm::vec3(26, -1, 0);
    state.enemies[14].speed = 3.0;
    state.enemies[14].aiType = VERTICAL_PATROLLER;
    state.enemies[14].aiState = PATROLY;
    state.enemies[14].isActive = true;

    state.enemies[16].textureID = patrollerTextureID;
    state.enemies[16].position = glm::vec3(28, -2, 0);
    state.enemies[16].spawn = glm::vec3(28, -2, 0);
    state.enemies[16].speed = 3.0;
    state.enemies[16].aiType = VERTICAL_PATROLLER;
    state.enemies[16].aiState = PATROLY;
    state.enemies[16].isActive = true;

    state.enemies[17].textureID = droneTextureID;
    state.enemies[17].position = glm::vec3(29.5, -3, 0);
    state.enemies[17].spawn = glm::vec3(29.5, -3, 0);
    state.enemies[17].speed = 1.5;
    state.enemies[17].aiType = VERTICAL_PATROLLER;
    state.enemies[17].aiState = PATROLY;
    state.enemies[17].isActive = true;

    state.enemies[18].textureID = patrollerTextureID;
    state.enemies[18].position = glm::vec3(31, -2.5, 0);
    state.enemies[18].spawn = glm::vec3(31, -2.5, 0);
    state.enemies[18].speed = 3.0;
    state.enemies[18].aiType = VERTICAL_PATROLLER;
    state.enemies[18].aiState = PATROLY;
    state.enemies[18].isActive = true;

    state.enemies[19].textureID = guardTextureID;
    state.enemies[19].position = glm::vec3(34, -4, 0);
    state.enemies[19].spawn = glm::vec3(34, -4, 0);
    state.enemies[19].speed = 1.0;
    state.enemies[19].aiType = GUARD;
    state.enemies[19].aiState = IDLE;
    state.enemies[19].isActive = true;

    state.enemies[20].textureID = guardTextureID;
    state.enemies[20].position = glm::vec3(1, -13, 0);
    state.enemies[20].spawn = glm::vec3(1, -13, 0);
    state.enemies[20].speed = 1.0;
    state.enemies[20].aiType = GUARD;
    state.enemies[20].aiState = IDLE;
    state.enemies[20].isActive = true;

    state.enemies[21].textureID = guardTextureID;
    state.enemies[21].position = glm::vec3(1, -20, 0);
    state.enemies[21].spawn = glm::vec3(1, -20, 0);
    state.enemies[21].speed = 0.5;
    state.enemies[21].aiType = GUARD;
    state.enemies[21].aiState = IDLE;
    state.enemies[21].isActive = true;

    state.enemies[22].textureID = guardTextureID;
    state.enemies[22].position = glm::vec3(3, -22, 0);
    state.enemies[22].spawn = glm::vec3(3, -22, 0);
    state.enemies[22].speed = 0.5;
    state.enemies[22].aiType = GUARD;
    state.enemies[22].aiState = IDLE;
    state.enemies[22].isActive = true;

    state.enemies[23].textureID = guardTextureID;
    state.enemies[23].position = glm::vec3(3.5, -26, 0);
    state.enemies[23].spawn = glm::vec3(3.5, -26, 0);
    state.enemies[23].speed = 1.0;
    state.enemies[23].aiType = GUARD;
    state.enemies[23].aiState = IDLE;
    state.enemies[23].isActive = true;

    state.enemies[24].textureID = guardTextureID;
    state.enemies[24].position = glm::vec3(2, -29, 0);
    state.enemies[24].spawn = glm::vec3(2, -29, 0);
    state.enemies[24].speed = 1.0;
    state.enemies[24].aiType = GUARD;
    state.enemies[24].aiState = IDLE;
    state.enemies[24].isActive = true;

    state.enemies[24].textureID = guardTextureID;
    state.enemies[24].position = glm::vec3(0, -33, 0);
    state.enemies[24].spawn = glm::vec3(0, -33, 0);
    state.enemies[24].speed = 0.9;
    state.enemies[24].aiType = GUARD;
    state.enemies[24].aiState = IDLE;
    state.enemies[24].isActive = true;

    state.enemies[25].textureID = guardTextureID;
    state.enemies[25].position = glm::vec3(7, -34, 0);
    state.enemies[25].spawn = glm::vec3(7, -34, 0);
    state.enemies[25].speed = 0.5;
    state.enemies[25].aiType = GUARD;
    state.enemies[25].aiState = IDLE;
    state.enemies[25].isActive = true;

    state.enemies[26].textureID = patrollerTextureID;
    state.enemies[26].position = glm::vec3(9, -30, 0);
    state.enemies[26].spawn = glm::vec3(9, -30, 0);
    state.enemies[26].speed = 0.9;
    state.enemies[26].aiType = HORIZONTAL_PATROLLER;
    state.enemies[26].aiState = PATROLY;
    state.enemies[26].isActive = true;

    state.enemies[27].textureID = patrollerTextureID;
    state.enemies[27].position = glm::vec3(34, -10, 0);
    state.enemies[27].spawn = glm::vec3(34, -10, 0);
    state.enemies[27].speed = 0.9;
    state.enemies[27].aiType = VERTICAL_PATROLLER;
    state.enemies[27].aiState = PATROLY;
    state.enemies[27].isActive = true;

    state.enemies[28].textureID = patrollerTextureID;
    state.enemies[28].position = glm::vec3(30, -15, 0);
    state.enemies[28].spawn = glm::vec3(30, -15, 0);
    state.enemies[28].speed = 0.9;
    state.enemies[28].aiType = HORIZONTAL_PATROLLER;
    state.enemies[28].aiState = PATROLX;
    state.enemies[28].isActive = true;

    state.enemies[29].textureID = patrollerTextureID;
    state.enemies[29].position = glm::vec3(35, -20, 0);
    state.enemies[29].spawn = glm::vec3(35, -20, 0);
    state.enemies[29].speed = 0.9;
    state.enemies[29].aiType = VERTICAL_PATROLLER;
    state.enemies[29].aiState = PATROLY;
    state.enemies[29].isActive = true;

    state.enemies[30].textureID = guardTextureID;
    state.enemies[30].position = glm::vec3(29, -20, 0);
    state.enemies[30].spawn = glm::vec3(29, -20, 0);
    state.enemies[30].speed = 0.9;
    state.enemies[30].aiType = GUARD;
    state.enemies[30].aiState = IDLE;
    state.enemies[30].isActive = true;

    state.enemies[31].textureID = droneTextureID;
    state.enemies[31].position = glm::vec3(24, -20, 0);
    state.enemies[31].spawn = glm::vec3(24, -20, 0);
    state.enemies[31].speed = 0.9;
    state.enemies[31].aiType = HORIZONTAL_PATROLLER;
    state.enemies[31].aiState = PATROLX;
    state.enemies[31].isActive = true;

    state.enemies[32].textureID = droneTextureID;
    state.enemies[32].position = glm::vec3(19, -20, 0);
    state.enemies[32].spawn = glm::vec3(19, -20, 0);
    state.enemies[32].speed = 0.9;
    state.enemies[32].aiType = HORIZONTAL_PATROLLER;
    state.enemies[32].aiState = PATROLX;
    state.enemies[32].isActive = true;

    state.enemies[33].textureID = droneTextureID;
    state.enemies[33].position = glm::vec3(16, -24, 0);
    state.enemies[33].spawn = glm::vec3(16, -24, 0);
    state.enemies[33].speed = 0.9;
    state.enemies[33].aiType = VERTICAL_PATROLLER;
    state.enemies[33].aiState = PATROLY;
    state.enemies[33].isActive = true;

    state.enemies[34].textureID = droneTextureID;
    state.enemies[34].position = glm::vec3(15, -30, 0);
    state.enemies[34].spawn = glm::vec3(15, -30, 0);
    state.enemies[34].speed = 0.9;
    state.enemies[34].aiType = HORIZONTAL_PATROLLER;
    state.enemies[34].aiState = PATROLX;
    state.enemies[34].isActive = true;

    state.enemies[35].textureID = guardTextureID;
    state.enemies[35].position = glm::vec3(20, -37, 0);
    state.enemies[35].spawn = glm::vec3(20, -37, 0);
    state.enemies[35].speed = 0.3;
    state.enemies[35].aiType = GUARD;
    state.enemies[35].aiState = IDLE;
    state.enemies[35].isActive = true;

    state.enemies[36].textureID = guardTextureID;
    state.enemies[36].position = glm::vec3(26, -37, 0);
    state.enemies[36].spawn = glm::vec3(26, -37, 0);
    state.enemies[36].speed = 0.5;
    state.enemies[36].aiType = GUARD;
    state.enemies[36].aiState = IDLE;
    state.enemies[36].isActive = true;

    state.enemies[37].textureID = guardTextureID;
    state.enemies[37].position = glm::vec3(33, -34, 0);
    state.enemies[37].spawn = glm::vec3(26, -37, 0);
    state.enemies[37].speed = 0.5;
    state.enemies[37].aiType = GUARD;
    state.enemies[37].aiState = IDLE;
    state.enemies[37].isActive = true;

    state.enemies[38].textureID = droneTextureID;
    state.enemies[38].position = glm::vec3(36, -34, 0);
    state.enemies[38].spawn = glm::vec3(36, -34, 0);
    state.enemies[38].speed = 1.0;
    state.enemies[38].aiType = VERTICAL_PATROLLER;
    state.enemies[38].aiState = PATROLY;
    state.enemies[38].isActive = true;

    state.enemies[39].textureID = droneTextureID;
    state.enemies[39].position = glm::vec3(35, -36, 0);
    state.enemies[39].spawn = glm::vec3(35, -36, 0);
    state.enemies[39].speed = 1.0;
    state.enemies[39].aiType = VERTICAL_PATROLLER;
    state.enemies[39].aiState = PATROLY;
    state.enemies[39].isActive = true;

    state.enemies[40].textureID = guardTextureID;
    state.enemies[40].position = glm::vec3(26, -25, 0);
    state.enemies[40].spawn = glm::vec3(26, -25, 0);
    state.enemies[40].speed = 1.0;
    state.enemies[40].aiType = GUARD;
    state.enemies[40].aiState = IDLE;
    state.enemies[40].isActive = true;

    state.enemies[41].textureID = droneTextureID;
    state.enemies[41].position = glm::vec3(27, -31  , 0);
    state.enemies[41].spawn = glm::vec3(27, -31, 0);
    state.enemies[41].speed = 1.0;
    state.enemies[41].aiType = HORIZONTAL_PATROLLER;
    state.enemies[41].aiState = PATROLX;
    state.enemies[41].isActive = true;
}

void Level1::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, ENEMY_COUNT, state.map);
    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, ENEMY_COUNT, state.map);
    }
}
void Level1::Render(ShaderProgram* program) {
    state.map->Render(program);
    for (int i = 0; i < ENEMY_COUNT; i++) state.enemies[i].Render(program);
    state.player->Render(program);
}
