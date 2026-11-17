#include "app.h"

#include "glad/include/glad/glad.h"

#include <GLFW/glfw3.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

App::App(){
  window = NULL;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}

int App::Initiate(){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnGraphics", NULL, NULL);

  if (window == NULL){
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return 0;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD" << std::endl;
    return 0;
  }

  return 1;
}

void App::Run(){
  while(!glfwWindowShouldClose(window)){
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
      glfwSetWindowShouldClose(window, true);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void App::Destroy(){
  glfwTerminate();
}


