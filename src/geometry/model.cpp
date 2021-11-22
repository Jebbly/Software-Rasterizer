#include "geometry/model.hpp"

Model::Model(const std::string &filepath) {
  // TO-DO: compute vertices from tinyobjloader
  Vertex v1, v2, v3;
  v1.position = glm::vec3(0, 1, 0);
  v2.position = glm::vec3(-2, 0.5, 0);
  v3.position = glm::vec3(1, 0, 0);
  vertices_.push_back(v1);
  vertices_.push_back(v2);
  vertices_.push_back(v3);

  indices_.push_back(0);
  indices_.push_back(1);
  indices_.push_back(2);

  max_pos_ = glm::vec3{1, 1, 0};
  min_pos_ = glm::vec3{-1, 0, 0};
}

const glm::vec3 &Model::GetMaxPosition() const { return max_pos_; }

const glm::vec3 &Model::GetMinPosition() const { return min_pos_; }

const Vertex &Model::GetVertex(size_t index) const {
  return vertices_.at(indices_.at(index));
}

size_t Model::GetIndexCount() const { return indices_.size(); }