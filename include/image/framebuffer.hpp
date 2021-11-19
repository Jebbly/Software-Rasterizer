#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "geometry/vertex.hpp"
#include <limits>
#include <stdexcept>
#include <stdlib.h>
#include <iostream>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

class Framebuffer {
public:
  Framebuffer();

  void Display() const;

  char &ColorAt(int x, int y);
  float &DepthAt(int x, int y);

private:
  char color_[WIDTH][HEIGHT];
  float depth_[WIDTH][HEIGHT];
};

#endif // FRAMEBUFFER_HPP