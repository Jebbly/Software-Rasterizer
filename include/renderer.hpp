#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "geometry/model.hpp"
#include "image/camera.hpp"
#include "image/framebuffer.hpp"
#include <iostream>
#include <limits>
#include <string>

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

  void ProjectToScreenSpace(glm::vec3& vertex) const;
  void ScreenSpaceToNDC(glm::vec3& coords) const;
};

#endif // RENDERER_HPP