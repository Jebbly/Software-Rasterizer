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
  // constructor initializes the resolution
  Renderer(const std::string &filepath);
  void Run();

private:
  Model model_;
  Camera camera_;
  Framebuffer buffer_;
  bool close_;

  void ProcessInput();
  void Draw();
};

#endif // RENDERER_HPP