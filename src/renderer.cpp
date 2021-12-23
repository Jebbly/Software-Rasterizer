#include "renderer.hpp"

Renderer::Renderer(const std::string &filepath)
    : model_{filepath}, close_{false} {
  // set camera position based on model size
  glm::vec3 max = model_.GetMaxPosition();
  glm::vec3 min = model_.GetMinPosition();

  // first compute the dimensions of the film canvas
  top_ = NEAR_CLIPPING_PLANE * (FILM_HEIGHT / 2) / FOCAL_LENGTH;
  right_ = NEAR_CLIPPING_PLANE * (FILM_WIDTH / 2) / FOCAL_LENGTH;

  if (FILM_ASPECT_RATIO > SCREEN_ASPECT_RATIO) {
    right_ *= SCREEN_ASPECT_RATIO / FILM_ASPECT_RATIO;
  } else {
    top_ *= FILM_ASPECT_RATIO / SCREEN_ASPECT_RATIO;
  }

  // move to rough average of model
  // and look down the negative Z-axis
  camera_.TranslateX((max.x + min.x) / 2);
  camera_.TranslateY((max.y + min.y) / 2);
  camera_.TranslateZ(max.z + 25);
  camera_.RotateX(180);

  // set controls
  controller_.EnableRawInput();
  rotation_speed_ = 0.5;
  movement_speed_ = 0.1;

  // find light position
  light_position_.x = std::max(max.x, max.z) + 25;
  light_position_.y = max.y + 5;
  light_rotation_ = 45.0;

  // clear screen before printing
  buffer_.Clear();
  buffer_.ResetScreen();
}

void Renderer::Run() {
  while (!close_) {
    Draw();
    ProcessInput();
  }
}

void Renderer::ProcessInput() {
  // TO-DO: Process input for camera movement and closing the application
  if (controller_.KeyboardHit()) {
    char input = controller_.GetInput();

    switch (input) {
      case 'x': {
        close_ = true;
        buffer_.Clear();
        buffer_.ResetScreen();
        controller_.RestoreSettings();
        break;
      }
      case 'w': {
        camera_.TranslateZ(movement_speed_);
        break;
      }
      case 's': {
        camera_.TranslateZ(-movement_speed_);
        break;
      }
      case 'e': {
        camera_.TranslateY(movement_speed_);
        break;
      }
      case 'q': {
        camera_.TranslateY(-movement_speed_);
        break;
      }
      case 'a': {
        camera_.TranslateX(-movement_speed_);
        break;
      }
      case 'd': {
        camera_.TranslateX(movement_speed_);
        break;
      }
      case 'i': {
        camera_.RotateY(rotation_speed_);
        break;
      }
      case 'k': {
        camera_.RotateY(-rotation_speed_);
        break;
      }
      case 'j': {
        camera_.RotateX(-rotation_speed_);
        break;
      }
      case 'l': {
        camera_.RotateX(rotation_speed_);
        break;
      }
      case '-': {
        movement_speed_ = std::max(movement_speed_ - 0.1, 0.1);
        break;
      }
      case '+': {
        movement_speed_ += 0.1;
        break;
      }
      case '[': {
        light_rotation_ -= 5;
        break;
      }
      case ']': {
        light_rotation_ += 5;
        break;
      }
    }
  }
}

void Renderer::Draw() {
  const glm::mat4 view_matrix = camera_.GetViewMatrix();

  for (size_t tri_idx = 0; tri_idx < model_.GetIndexCount(); tri_idx += 3) {
    // compute the vertices of the triangle in camera space
    // then find their position in screen space
    // also keep track of the maximum and minimum screen coords
    Vertex triangle[3];
    glm::vec2 min_coord{SCREEN_WIDTH, SCREEN_HEIGHT}, max_coord{0, 0};
    glm::vec3 coords[3];
    for (size_t i = 0; i < 3; i++) {
      triangle[i] = view_matrix * model_.GetVertex(tri_idx + i);
      coords[i] = ProjectToScreenSpace(triangle[i].position);
      coords[i] = ScreenSpaceToNDC(coords[i]);
      coords[i] = NDCToRasterSpace(coords[i]);

      // if triangle is used, re-adjust triangle boundaries
      if (coords[i].x < min_coord.x) {
        min_coord.x = std::max<float>(coords[i].x, 0);
      } 
      
      if (coords[i].x > max_coord.x) {
        max_coord.x = std::min<float>(coords[i].x, SCREEN_WIDTH - 1);
      }

      if (coords[i].y < min_coord.y) {
        min_coord.y = std::max<float>(coords[i].y, 0);
      }
      
      if (coords[i].y > max_coord.y) {
        max_coord.y = std::min<float>(coords[i].y, SCREEN_HEIGHT - 1);
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

          if (depth < buffer_.DepthAt(x, y) && depth > 0) {
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
  buffer_.Clear();
}

// this function assumes that the vertex is already in camera space
glm::vec3 Renderer::ProjectToScreenSpace(const glm::vec3& vertex) const {
  glm::vec3 projected_vertex;
  projected_vertex.x = vertex.x / -vertex.z;
  projected_vertex.y = CHARACTER_ASPECT_RATIO * vertex.y / -vertex.z;
  // TO-DO: better depth handling (involving clipping planes)
  projected_vertex.z = -vertex.z;
  projected_vertex *= FOCAL_LENGTH;
  return projected_vertex;
}

// this function assumes that the vertex is already in screen space
glm::vec3 Renderer::ScreenSpaceToNDC(const glm::vec3& coords) const {
  // max screen-space coords should depend on camera config
  glm::vec3 new_coords;
  new_coords.x = coords.x / right_;
  new_coords.y = coords.y / top_;
  new_coords.z = coords.z;
  return new_coords;
}

// this function converts NDC coordinates to the raster space
glm::vec3 Renderer::NDCToRasterSpace(const glm::vec3 &coords) const {
  glm::vec3 new_coords;
  new_coords.x = (coords.x + 1) / 2 * SCREEN_WIDTH;
  new_coords.y = (coords.y + 1) / 2 * SCREEN_HEIGHT;
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
  // find how directly the triangle is pointing at the light source
  // light source currently is positioned at whereever the camera is
  glm::vec3 light_pos = glm::vec3(light_position_.x * sin(glm::radians(light_rotation_)), light_position_.y, light_position_.x * cos(glm::radians(light_rotation_)));
  glm::vec3 light_dir = glm::normalize(light_pos - position);
  float diffuse = std::clamp(glm::dot(normal, glm::normalize(light_dir)), 0.f, 1.f);

  // find the distance from the light source
  float attenuation = 1 / (0.04 * glm::distance(light_pos, position));

  // index the ASCII palette according to brightness
  const std::string palette = " .:-=+*#%@";
  return palette[std::clamp((int)(((diffuse) * palette.length()) * attenuation), 0, (int) palette.length() - 1)];
}