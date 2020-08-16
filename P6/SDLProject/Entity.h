#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif
 
#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#include "Map.h"
#include "Util.h"

enum EntityType {PLAYER, PLATFORM, ENEMY};

enum AIType { FOLLOWER, GUARD, VERTICAL_PATROLLER, HORIZONTAL_PATROLLER};
enum AIState {IDLE, FOLLOW, PATROL};

class Entity {
public:
    EntityType entityType;
    AIType aiType;
    AIState aiState;

    glm::vec3 position;
    glm::vec3 movement;
    glm::vec3 velocity;
    glm::vec3 spawn; 

    float width = 1;
    float height = 1;

    bool jump = false;
    float jumpPower = 6;

    float speed;

    GLuint textureID;

    glm::mat4 modelMatrix;

    int* animRight = NULL;
    int* animLeft = NULL;
    int* animUp = NULL;
    int* animDown = NULL;

    int* animIndices = NULL;
    int animFrames = 0;
    int animIndex = 0;
    float animTime = 0;
    int animCols = 0;
    int animRows = 0;

    bool isActive = true;

    bool collidedTop = false;
    bool collidedBottom = false;
    bool collidedLeft = false;
    bool collidedRight = false;

    bool hit = true; // Collision will hurt

    int lives;

    Entity();

    bool CheckCollision(Entity *other);
    void CheckCollisionsY(Entity* objects, int objectCount);
    void CheckCollisionsX(Entity* objects, int objectCount);
    void CheckCollisionsY(Map* map);
    void CheckCollisionsX(Map* map);
    void CheckCollisionsXY(Map* map);

    void CheckIfPlayerKilled(Entity* enemies, int enemyCount);
    void Update(float deltaTime, Entity* player, Entity* objects, int objectCount, Map* map);
    void Render(ShaderProgram* program);
    void DrawSpriteFromTextureAtlas(ShaderProgram* program, GLuint textureID, int index);

    void AI(Entity *player);
    void AIWalker();
    void AIWaitAndGo(Entity *player);
    void AILurcher(Entity *player);
    void AIGlider(Entity *player);
    void AIFollower(Entity* player);
    void AIGuard(Entity* player);
    void AIVerticalPatroller(Entity* player);
    void AIHorizontalPatroller(Entity* player);
};