#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>

struct Vertex {
  Vertex() = default;

  glm::vec3 position;
  glm::vec3 normal;
};

// handle transformations for attributes differently
Vertex operator*(const glm::mat4 &matrix, const Vertex &vertex);
Vertex operator*(const Vertex &vertex, const Vertex &matrix);

#endif // VERTEX_HPP