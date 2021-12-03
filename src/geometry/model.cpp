#include "geometry/model.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

Model::Model(const std::string &filepath) : max_pos_{std::numeric_limits<float>::min()}, min_pos_{std::numeric_limits<float>::max()} {
  // Compute vertices from tinyobjloader
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn, err;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str())) {
    throw std::runtime_error(warn + err);
  }

  for (const auto& shape : shapes) {
    for (const auto& index : shape.mesh.indices) {
      Vertex vertex{};

      // vertex attrib arrays contain 3 float elements per vertex
      // so the vertex index needs to be offset appropriately
      vertex.position = {
        attrib.vertices[3 * index.vertex_index + 0],
        attrib.vertices[3 * index.vertex_index + 1],
        attrib.vertices[3 * index.vertex_index + 2]
      };

      vertex.normal = {
        attrib.normals[3 * index.vertex_index + 0],
        attrib.normals[3 * index.vertex_index + 1],
        attrib.normals[3 * index.vertex_index + 2]
      };

      if (vertex.position.x < min_pos_.x) {
        min_pos_.x = vertex.position.x;
      }

      if (vertex.position.y < min_pos_.y) {
        min_pos_.y = vertex.position.y;
      }

      if (vertex.position.z < min_pos_.z) {
        min_pos_.z = vertex.position.z;
      }

      if (vertex.position.x > max_pos_.x) {
        max_pos_.x = vertex.position.x;
      }

      if (vertex.position.y > max_pos_.y) {
        max_pos_.y = vertex.position.y;
      }

      if (vertex.position.z > max_pos_.z) {
        max_pos_.z = vertex.position.z;
      }

      vertices_.push_back(vertex);
      indices_.push_back(indices_.size());
    }
  }
}

const glm::vec3 &Model::GetMaxPosition() const { return max_pos_; }

const glm::vec3 &Model::GetMinPosition() const { return min_pos_; }

const Vertex &Model::GetVertex(size_t index) const {
  return vertices_.at(indices_.at(index));
}

size_t Model::GetIndexCount() const { return indices_.size(); }