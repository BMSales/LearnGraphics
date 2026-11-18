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

void App::shaderEditorWindow(Shader& shaderProgram){
  ImGui::SetNextWindowSize(ImVec2(500.0f, 500.0f), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowPos(ImVec2(400.0f, 300.0f), ImGuiCond_FirstUseEver);

  ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize;

  static char text[1024 * 16] = "test\n";
  if(ImGui::Begin("TEST", nullptr, flags)){
    ImGui::InputTextMultiline("test", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, 200.0f), ImGuiInputTextFlags_AllowTabInput);
    if(ImGui::Button("RELOAD")){
      std::ofstream out("./shaders/vertex.glsl");
      out << text;
      out.close();
      shaderProgram.reload("./shaders/vertex.glsl", "./shaders/fragment.glsl");
    }
    if(ImGui::Button("CLOSE")){
      glfwSetWindowShouldClose(window, true);
    }
  }

  ImGui::End();
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

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();

  return 1;
}

void App::Run(){
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
    0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f
  };

  unsigned int indices[] = {
    0, 1, 2
  };

  Shader shaderProgram = Shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");

  unsigned int VBO;
  unsigned int VAO;
  unsigned int EBO;
  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  shaderProgram.use();

  while(!glfwWindowShouldClose(window)){
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.use();

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    shaderEditorWindow(shaderProgram);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
      shaderProgram.reload("./shaders/vertex.glsl", "./shaders/fragment.glsl");
    }

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
