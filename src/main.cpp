#include "include/imgui.h"
#include "include/imgui_impl_sdl2.h"
#include "include/imgui_impl_opengl3.h"
#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(){
  SDL_Window* window = NULL;

  SDL_Surface* screenSurface = NULL;

  SDL_GLContext My_SDL_Context;

  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    std::cout << "SDL could not initialize! SDL_ERROR: " << SDL_GetError() << std::endl;
  }

  window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if(window == NULL){
    std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
  }

  screenSurface = SDL_GetWindowSurface(window);

  My_SDL_Context = SDL_GL_CreateContext(window);
  
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

  SDL_UpdateWindowSurface(window);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui_ImplSDL2_InitForOpenGL(window, My_SDL_Context);
  ImGui_ImplOpenGL3_Init();

  SDL_Event event;
  bool quit = false;

  while(quit == false){
    while(SDL_PollEvent(&event)){
      ImGui_ImplSDL2_ProcessEvent(&event);
      if(event.type == SDL_QUIT){
        quit = true;
        std::cout << "SDL Window closed." << std::endl;
      }
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
