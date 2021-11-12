#include "model.hpp"

Model::Model(const std::string &filepath) {
  // test if glm works
  std::cout << "Processing " << filepath << std::endl;
  vertices_.push_back(glm::vec3{0.0, 0.0, 0.0});
}