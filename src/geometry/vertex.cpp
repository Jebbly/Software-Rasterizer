#include "geometry/vertex.hpp"

Vertex operator*(const glm::mat4 &matrix, const Vertex &vertex) {
  Vertex product;
  product.position = matrix * glm::vec4(vertex.position, 1);
  // TO-DO: Calculate transformed normal
  return product;
}

Vertex operator*(const Vertex &vertex, const Vertex &matrix) {
  return matrix * vertex;
}