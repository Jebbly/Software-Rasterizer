#include "renderer.hpp"

Renderer::Renderer(const std::string &filepath)
    : model_{filepath}, close_{false} {
  // set camera position based on model size
  glm::vec3 max = model_.GetMaxPosition();
  glm::vec3 min = model_.GetMinPosition();

  // move to rough average of model
  // and look down the negative Z-axis
  camera_.TranslateX((max.x + min.x) / 2);
  camera_.TranslateY((max.y + min.y) / 2);
  camera_.TranslateZ(15);
  camera_.RotateX(180);
}

void Renderer::Run() {
  while (!close_) {
    ProcessInput();
    Draw();
    break;
  }
}

void Renderer::ProcessInput() {
  // TO-DO: Process input for camera movement and closing the application
  std::cout << "Process input here" << std::endl;
}

void Renderer::Draw() {
  const glm::mat4 view_matrix = camera_.GetViewMatrix();
  for (size_t tri_idx = 0; tri_idx < model_.GetIndexCount(); tri_idx += 3) {
    // compute the vertices of the triangle in camera space
    // then find their position in screen space
    // also keep track of the maximum and minimum screen coords
    Vertex triangle[3];
    glm::vec2 min_coord{WIDTH, HEIGHT}, max_coord{0, 0};
    glm::vec3 coords[3];
    for (size_t i = 0; i < 3; i++) {
      triangle[i] = view_matrix * model_.GetVertex(tri_idx + i);
      coords[i] = ProjectToScreenSpace(triangle[i].position);
      coords[i] = ScreenSpaceToNDC(coords[i]);

      // if triangle is used, re-adjust triangle boundaries
      if (coords[i].x < min_coord.x) {
        min_coord.x = std::max<float>(coords[i].x, 0);
      } 
      
      if (coords[i].x > max_coord.x) {
        max_coord.x = std::min<float>(coords[i].x, WIDTH - 1);
      }

      if (coords[i].y < min_coord.y) {
        min_coord.y = std::max<float>(coords[i].y, 0);
      }
      
      if (coords[i].y > max_coord.y) {
        max_coord.y = std::min<float>(coords[i].y, HEIGHT - 1);
      }
    }

    // only need to iterate through the bounding box of the triangle
    for (int y = min_coord.y; y <= max_coord.y; y++) {
      for (int x = min_coord.x; x <= max_coord.x; x++) {
        glm::vec2 pixel{x, y};
        
        // test if pixel is inside of boundaries
        float weights[3];
        bool inside_triangle = true;
        for (size_t i = 0; i < 3; i++) {
          weights[i] = EdgeFunction(coords[i], coords[(i + 1) % 3], pixel) + 0.0001;
          if (weights[i] < 0) {
            inside_triangle = false;
            break;
          }
        }

        if (inside_triangle) {
          // edge function also returns area 
          // to compute barycentric coordinates for vertex attribute interpolation
          float area = EdgeFunction(coords[0], coords[1], coords[2]);
          float depth = 0;
          for (size_t i = 0; i < 3; i++) {
            weights[i] /= area;
            depth += weights[i] * coords[i].z;
          }

          if (depth < buffer_.DepthAt(x, y)) {
            glm::vec3 position{0, 0, 0};
            for (size_t i = 0; i < 3; i++) {
              position += weights[i] * triangle[i].position;
            }

            glm::vec3 normal =
                glm::cross(triangle[1].position - triangle[0].position,
                           triangle[2].position - triangle[0].position);
            buffer_.ColorAt(x, y) = Shade(position, glm::normalize(normal));
            buffer_.DepthAt(x, y) = depth;
          }
        }
      }
    }
  }

  buffer_.Display();
}

// this function assumes that the vertex is already in camera space
glm::vec3 Renderer::ProjectToScreenSpace(const glm::vec3& vertex) const {
  glm::vec3 projected_vertex;
  projected_vertex.x = CHARACTER_ASPECT_RATIO * vertex.x / abs(vertex.z);
  projected_vertex.y = vertex.y / abs(vertex.z);
  // TO-DO: better depth handling (involving clipping planes)
  projected_vertex.z = -vertex.z;
  projected_vertex *= FOCAL_LENGTH;
  return projected_vertex;
}

// this function assumes that the vertex is already in screen space
glm::vec3 Renderer::ScreenSpaceToNDC(const glm::vec3& coords) const {
  // max screen-space coords should depend on camera config
  glm::vec3 new_coords;
  new_coords.x = coords.x + WIDTH/2;
  new_coords.y = coords.y + HEIGHT/2;
  new_coords.z = coords.z;
  return new_coords;
}

// this function determines if p is to the left (-) or right (+)
// of the line segment formed between v1 and v2
float Renderer::EdgeFunction(const glm::vec2& v1, const glm::vec2& v2, const glm::vec2& p) const {
  glm::vec3 e1 = glm::vec3(p - v1, 0);
  glm::vec3 e2 = glm::vec3(v2 - v1, 0);
  return -glm::cross(e1, e2).z;
}

// this function determines which character to represent the pixel
// depending on the distance and orientation of the triangle
char Renderer::Shade(const glm::vec3& position, const glm::vec3& normal) const {
  // any triangle should have a default minimum lighting
  float ambient = 0.1;

  // find how directly the triangle is pointing at the light source
  // light source currently is positioned at whereever the camera is
  glm::vec3 light_dir = glm::normalize(camera_.GetPosition() - position);
  float diffuse = std::clamp(glm::dot(normal, glm::normalize(light_dir)), 0.f, 1.f);

  // find the distance from the light source
  float attenuation = 1 / (0.04 * glm::distance(camera_.GetPosition(), position));

  // index the ASCII palette according to brightness
  const char palette[] = " .:-=+*#%@";
  return palette[std::clamp((int)(((ambient + diffuse) * 10) * attenuation) , 0, 9)];
}