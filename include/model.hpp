#ifndef MODEL_HPP
#define MODEL_HPP

#include <exception>
#include <glm/vec3.hpp>
#include <iostream>
#include <string>
#include <vector>

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
};

class Model {
public:
  Model(const std::string &filepath);

private:
  std::vector<Vertex> vertices_;

  glm::vec3 max_pos_;
  glm::vec3 min_pos_;
};

#endif // MODEL_HPP