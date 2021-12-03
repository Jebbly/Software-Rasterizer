#include "geometry/vertex.hpp"

Vertex operator*(const glm::mat4 &matrix, const Vertex &vertex) {
  Vertex product;
  product.position = matrix * glm::vec4(vertex.position, 1);
  // ignore translations when calculating the normal
  // since we're never going to perform a model transformation
  // we can use the same matrix as the normal matrix
  // since the camera's view matrix is already orthogonal
  product.normal = glm::normalize(matrix * glm::vec4(vertex.normal, 0));
  return product;
}

Vertex operator*(const Vertex &vertex, const Vertex &matrix) {
  return matrix * vertex;
}