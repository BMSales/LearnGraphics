#include "app.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

App::App(){
  window = NULL;
}

void App::Initiate(){
  if(SDL_Init(SDL_INIT_VIDEO) < 0){
    std::cout << "SDL could not initialize! SDL_ERROR: " << SDL_GetError() << std::endl;
  }

  window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if(window == NULL){
    std::cout << "Window could not be created! SDL_ERROR: " << SDL_GetError() << std::endl;
  }
}

void App::Run(){
  SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
  SDL_GLContext sdlContext = SDL_GL_CreateContext(window);
  SDL_Event event;
  bool quit = false;

  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(window);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui_ImplSDL2_InitForOpenGL(window, sdlContext);
  ImGui_ImplOpenGL3_Init();

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
}

void App::Destroy(){
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyWindow(window);
  SDL_Quit();
}
