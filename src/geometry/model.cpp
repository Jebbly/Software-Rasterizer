#include "geometry/model.hpp"

Model::Model(const std::string &filepath) {
  // TO-DO: compute vertices from tinyobjloader
}

const glm::vec3 &Model::GetMaxPosition() const { return max_pos_; }

const glm::vec3 &Model::GetMinPosition() const { return min_pos_; }

const Vertex &Model::GetVertex(size_t index) const {
  return vertices_.at(indices_.at(index));
}

size_t Model::GetIndexCount() const { return indices_.size(); }