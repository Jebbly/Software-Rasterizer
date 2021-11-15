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
  // TO-DO: Process input for camera movement and closing the application
  std::cout << "Process input here" << std::endl;
}

void Renderer::Draw() {
  const glm::mat4 view_matrix = camera_.GetViewMatrix();
  for (size_t tri_idx = 0; tri_idx < model_.GetIndexCount(); tri_idx += 3) {
    // compute the vertices of the triangle in camera space
    Vertex triangle[3];
    for (size_t i = 0; i < 3; i++) {
      triangle[i] = view_matrix * model_.GetVertex(tri_idx + i);
    }

    // TO-DO: project triangle onto framebuffer

    // TO-DO: iterate through pixels to check triangle coverage
  }
}