#pragma once

#include <SDL.h>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

class App {
  public:
    App();
    void Initiate();
    void Run();
    void Destroy();

  private:
    SDL_Window* window;
};
