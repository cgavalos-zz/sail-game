#include <chrono>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include "InitWorld.h"
#include "World.h"

auto t = std::chrono::high_resolution_clock::now();

void renderInit() {

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void render(World &world, SDL_Window *win, Uint32 &pastTicks,
            unsigned int &numFrames, unsigned int &fps) {

  const float timeThresh = 0.25f;

  Uint32 current = SDL_GetTicks();

  if (current - pastTicks > timeThresh * 1000) {
    float tempFps = numFrames * 1000.0f / (current - pastTicks);
    fps = (unsigned int)tempFps;
    pastTicks = current;
    numFrames = 0;

    SDL_SetWindowTitle(win, std::to_string(fps).c_str());
  }

  numFrames++;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  auto now = std::chrono::high_resolution_clock::now();
  auto nanos =
      std::chrono::duration_cast<std::chrono::nanoseconds>(now - t).count();
  t = now;
  auto timeStep = (float)nanos / 1.0e9f;

  world.update(timeStep);

  SDL_GL_SwapWindow(win);
  SDL_Delay(1000 / 60);
}

bool shouldQuit(SDL_Event *e) {

  SDL_PollEvent(e);
  return (*e).type == SDL_QUIT;
}

int init(unsigned int width, unsigned int height, SDL_Window **win,
         SDL_GLContext *con) {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  *win = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED, width, height,
                          SDL_WINDOW_OPENGL);
  if (*win == nullptr) {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
  }

  *con = SDL_GL_CreateContext(*win);
  if (*con == nullptr) {
    std::cout << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
  }

  if (SDL_GL_MakeCurrent(*win, *con) != 0) {
    std::cout << "MakeCurrent failed" << std::endl;
    return EXIT_FAILURE;
  }

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "glewInit failed: " << glewGetErrorString(err) << std::endl;
    return EXIT_FAILURE;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  return EXIT_SUCCESS;
}

void cleanup(SDL_Window *win, SDL_GLContext con) {

  SDL_GL_DeleteContext(con);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

int main() {
  float eyeHorizontalFOV = 210.0f;
  float eyeVerticalFOV = 150.0f;
  const unsigned int width = 1280;
  const unsigned int height = eyeVerticalFOV * (float)width / eyeHorizontalFOV;

  SDL_Window *win;
  SDL_GLContext con;

  if (init(width, height, &win, &con) == EXIT_FAILURE) {
    std::cout << "Init Error" << std::endl;
    return EXIT_FAILURE;
  }

  renderInit();

  SDL_GL_SetSwapInterval(1);

  SDL_Event e;
  SDL_PollEvent(&e);

  World world;
  initWorld(&world);

  Uint32 pastTicks = 0;
  unsigned int numFrames = 0;
  Uint32 fps = 0;

  while (!shouldQuit(&e)) {

    render(world, win, pastTicks, numFrames, fps);
  }

  cleanup(win, con);
  return EXIT_SUCCESS;
}
