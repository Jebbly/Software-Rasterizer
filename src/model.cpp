#include "model.hpp"

Model::Model(const std::string &filepath) {
  // compute vertices from tinyobjloader
}

const glm::vec3& Model::GetMaxPosition() const {
  return max_pos_;
}

const glm::vec3& Model::GetMinPosition() const {
  return min_pos_;
}