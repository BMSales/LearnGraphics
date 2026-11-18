#pragma once

#include <iostream>

#include "../deps/imgui/imgui.h"
#include "../deps/imgui/backends/imgui_impl_glfw.h"
#include "../deps/imgui/backends/imgui_impl_opengl3.h"

#include "shader.h"

class App {
  public:
    App();
    int Initiate();
    void Run();
    void Destroy();

  private:
    void shaderEditorWindow(Shader&);
    GLFWwindow* window;
};
