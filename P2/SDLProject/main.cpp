#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix,
          blue_paddle_matrix, red_paddle_matrix, ball_matrix;

glm::vec3 paddle_scale = glm::vec3(0.3f, 2.0f, 1.0f);
float paddle_height = paddle_scale.y;
float paddle_width = paddle_scale.x;
glm::vec3 blue_position = glm::vec3(-4.5, 0, 0);
glm::vec3 blue_movement = glm::vec3(0, 0, 0);
float blue_speed = 5.0f;
glm::vec3 red_position = glm::vec3(4.5, 0, 0);
glm::vec3 red_movement = glm::vec3(0, 0, 0);
float red_speed = 5.0f;

glm::vec3 ball_scale = glm::vec3(0.5f, 0.5f, 1.0f);
float ball_height = ball_scale.y;
float ball_width = ball_scale.x;
glm::vec3 ball_position = glm::vec3(0, 0, 0);
glm::vec3 ball_movement = glm::vec3(0, 0, 0);
float ball_speed = 5.0f;

GLuint blue_paddle_TextureID;
GLuint red_paddle_TextureID;
GLuint ball_TextureID;

bool gameStart = true;

Mix_Music *music;
Mix_Chunk* bounce;

GLuint LoadTexture(const char* filePath) {
    int w, h, n;
    unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);
    if (image == NULL) {
        std::cout << "Unable to load image. Make sure the path is correct\n";
        assert(false);
    }
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(image);
    return textureID;
}

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    displayWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(0, 0, 640, 480);

    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("dooblydoo.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);

    bounce = Mix_LoadWAV("bounce.wav");

    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);

    glUseProgram(program.programID);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    blue_paddle_TextureID = LoadTexture("blue paddle.png");
    red_paddle_TextureID = LoadTexture("red paddle.png");
    ball_TextureID = LoadTexture("orange circle.png");
}

//Check if paddle can move (between walls) and then change the direction based on the input key.
float move_blue_paddle(float y, float paddle_height, const Uint8* keys) {
    if (y + paddle_height / 2.0f > 3.7f) return -1.0f; // Move the paddle back into bounds if it is outside.
    else if (y - paddle_height / 2.0f < -3.7f) return 1.0f;
    else if ((y + paddle_height / 2.0f < 3.7f) &&
       (y - paddle_height / 2.0f > -3.7f)) {
       if (keys[SDL_SCANCODE_W]) return 1.0f;
       else if (keys[SDL_SCANCODE_S]) return -1.0f;
    }
   return 0.0f;
}

//Check if paddle can move (between walls) and then change the direction based on the input key.
float move_red_paddle(float y, float paddle_height, const Uint8* keys) {
    if (y + paddle_height / 2.0f > 3.7f) return -1.0f; // Move the paddle back into bounds if it is outside.
    else if (y - paddle_height / 2.0f < -3.7f) return 1.0f;
    else if ((y + paddle_height / 2.0f < 3.7f) &&
        (y - paddle_height / 2.0f > -3.7f)) {
        if (keys[SDL_SCANCODE_UP]) return 1.0f;
        else if (keys[SDL_SCANCODE_DOWN]) return -1.0f;
    }
    return 0.0f;
}

void ProcessInput() {
    blue_movement = glm::vec3(0); 
    red_movement = glm::vec3(0);
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                gameIsRunning = false;
                break;
        }
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    // Ball starts moving right when space is pressed (game start)
    if (keys[SDL_SCANCODE_SPACE] && gameStart) {
        ball_movement.x = rand() % 5; //Start with a random direction for the ball to move in.
        ball_movement.y = rand() % 5;
        gameStart = false;
    }
    if (glm::length(ball_movement) > 1.0f) ball_movement = glm::normalize(ball_movement);
    blue_movement.y = move_blue_paddle(blue_position.y, paddle_height, keys);
    if (glm::length(blue_movement) > 1.0f) blue_movement = glm::normalize(blue_movement);
    red_movement.y = move_red_paddle(red_position.y, paddle_height, keys);
    if (glm::length(red_movement) > 1.0f) red_movement = glm::normalize(red_movement);
}    

float lastTicks = 0.0f;

void Update() {
    if (ball_position.x > 4.8f || ball_position.x < -4.8f) gameIsRunning = false;
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;

    ball_matrix = glm::mat4(1.0f);
    //If the ball hits a horizontal wall (ceiling or floor), reverse its y direction.
    if (ball_position.y + ball_height / 2.0f > 3.7f) {
        Mix_PlayChannel(-1, bounce, 0);
        ball_position.y = 3.4f; // This fixes the glitch of the ball getting stuck reversing its "y"
                                // movement within the ceiling by resetting the ball slightly under
                                // the ceiling.
        ball_movement.y *= -1.0f;
    }
    else if (ball_position.y - ball_height / 2.0f < -3.7f) {
        Mix_PlayChannel(-1, bounce, 0);
        ball_position.y = -3.4f; // This fixes the glitch of the ball getting stuck reversing its "y"
                                // movement within the floor by resetting the ball slightly above
                                // the floor.
        ball_movement.y *= -1.0f;
    }
    //If the ball hits a paddle, reverse its x direction.
    else if ((fabs(red_position.x - ball_position.x) - ((ball_width - 0.1f + paddle_width) / 2) < 0 &&
              fabs(red_position.y - ball_position.y) - ((ball_height - 0.1f + paddle_height) / 2) < 0)) {
        Mix_PlayChannel(-1, bounce, 0);
        ball_position.x -= 0.1f; // This fixes the glitch of the ball getting stuck reversing its "x"
                                 // movement in within the boundaries of the paddle by resetting the
                                 // ball outside of the boundary.
        ball_movement.x *= -1.0f;
   }
    else if ((fabs(blue_position.x - ball_position.x) - ((ball_width - 0.1f + paddle_width) / 2) < 0 &&
              fabs(blue_position.y - ball_position.y) - ((ball_height - 0.1f + paddle_height) / 2) < 0)) {
        Mix_PlayChannel(-1, bounce, 0);
        ball_position.x += 0.1f; // This fixes the glitch of the ball getting stuck reversing its "x"
                                 // movement in within the boundaries of the paddle by resetting the
                                 // ball outside of the boundary.
        ball_movement.x *= -1.0f;
    }

    ball_position += ball_movement * ball_speed * deltaTime;
    ball_matrix = glm::translate(ball_matrix, ball_position);
    ball_matrix = glm::scale(ball_matrix, ball_scale);

    blue_position += blue_movement * blue_speed * deltaTime;
    blue_paddle_matrix = glm::mat4(1.0f);
    blue_paddle_matrix = glm::translate(blue_paddle_matrix, blue_position);
    blue_paddle_matrix = glm::scale(blue_paddle_matrix, paddle_scale);
    
    red_position += red_movement * red_speed * deltaTime;
    red_paddle_matrix = glm::mat4(1.0f);
    red_paddle_matrix = glm::translate(red_paddle_matrix, red_position);
    red_paddle_matrix = glm::scale(red_paddle_matrix, paddle_scale);
}

void draw_ball() {
    program.SetModelMatrix(ball_matrix);
    glBindTexture(GL_TEXTURE_2D, ball_TextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void draw_blue_paddle() {
    program.SetModelMatrix(blue_paddle_matrix);
    glBindTexture(GL_TEXTURE_2D, blue_paddle_TextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void draw_red_paddle() {
    program.SetModelMatrix(red_paddle_matrix);
    glBindTexture(GL_TEXTURE_2D, red_paddle_TextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };

    program.SetModelMatrix(modelMatrix);

    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program.texCoordAttribute);

    draw_ball();
    draw_blue_paddle();
    draw_red_paddle();

    glDisableVertexAttribArray(program.positionAttribute);
    glDisableVertexAttribArray(program.texCoordAttribute);

    SDL_GL_SwapWindow(displayWindow);
}

void Shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();

    while (gameIsRunning) {
        ProcessInput();
        Update();
        Render();
    }

    Shutdown();
    return 0;
}