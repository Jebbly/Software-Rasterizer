#include "renderer.hpp"

Renderer::Renderer(const std::string &filepath)
    : model_{filepath}, close_{false} {
    // set camera position based on model size
    glm::vec3 max = model_.GetMaxPosition();
    glm::vec3 min = model_.GetMinPosition();

    camera_.TranslateX((max.x + min.x) / 2);
    camera_.TranslateY((max.y + min.y) / 2);
    camera_.TranslateZ(min.z - max.z);
}

void Renderer::Run() {
  while (!close_) {
    ProcessInput();
    Draw();
  }
}

void Renderer::ProcessInput() {
  std::cout << "Process input here" << std::endl;
}

void Renderer::Draw() { std::cout << "Draw here" << std::endl; }