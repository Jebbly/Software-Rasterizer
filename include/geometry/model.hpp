#ifndef MODEL_HPP
#define MODEL_HPP

#include "vertex.hpp"
#include <exception>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

class Model {
public:
  Model(const std::string &filepath);

  const glm::vec3 &GetMaxPosition() const;
  const glm::vec3 &GetMinPosition() const;

  const Vertex &GetVertex(size_t index) const;
  size_t GetIndexCount() const;

private:
  std::vector<Vertex> vertices_;
  std::vector<int> indices_;
  int num_triangles_;

  glm::vec3 max_pos_;
  glm::vec3 min_pos_;
};

#endif // MODEL_HPP