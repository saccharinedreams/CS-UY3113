#include "menu.h"
#define MENU_WIDTH 11
#define MENU_HEIGHT 8

unsigned int menu_data[] =
{
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void menu::Initialize() {

    state.nextScene = 0;
    GLuint mapTextureID = Util::LoadTexture("laser_tileset.png");
    state.map = new Map(MENU_WIDTH, MENU_HEIGHT, menu_data, mapTextureID, 1.0f, 4, 1);
    // Initialize Game Objects
    // Initialize Player    
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(4, -2, 0);
    state.player->movement = glm::vec3(0);
    state.player->speed = 3.5f;
    state.player->height = 0.8f;
    state.player->width = 0.7f;
    state.player->textureID = Util::LoadTexture("player.png");
}

void menu::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, 0, state.map);
  
    if (state.player->position.x >= 12) state.nextScene = 1;
}
void menu::Render(ShaderProgram* program) {
    Util::DrawText(program, Util::LoadTexture("font.png"), "Escape",
        0.6f, 0.2f, glm::vec3(1.50f, -0.5f, 0));
    Util::DrawText(program, Util::LoadTexture("font.png"), "Area 51",
        0.4f, 0.1f, glm::vec3(2.75f, -1.0f, 0));
    Util::DrawText(program, Util::LoadTexture("font.png"), 
        "Press Enter!",
        0.25f, 0.0f, glm::vec3(1.0f, -4.0f, 0));
    state.map->Render(program);
    state.player->Render(program);
   
}
