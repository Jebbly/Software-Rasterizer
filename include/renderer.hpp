#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "geometry/model.hpp"
#include "image/camera.hpp"
#include "image/framebuffer.hpp"
#include <glm/gtx/string_cast.hpp> 
#include <iostream>
#include <limits>
#include <string>

#define NEAR_CLIPPING_PLANE 0.1
#define FAR_CLIPPING_PLANE 1000
#define FOCAL_LENGTH 300

class Renderer {
public:
  Renderer(const std::string &filepath);
  void Run();

private:
  Model model_;
  Camera camera_;
  Framebuffer buffer_;
  bool close_;

  void ProcessInput();
  void Draw();

  glm::vec3 ProjectToScreenSpace(const glm::vec3& vertex) const;
  glm::vec3 ScreenSpaceToNDC(const glm::vec3& coords) const;
  float EdgeFunction(const glm::vec2& v1, const glm::vec2& v2, const glm::vec2& p) const;
  char Shade(const glm::vec3& position, const glm::vec3& normal) const;
};

#endif // RENDERER_HPP