#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "geometry/vertex.hpp"
#include <limits>
#include <stdexcept>
#include <stdlib.h>
#include <iostream>

constexpr int WIDTH = 100;
constexpr int HEIGHT = 40;

class Framebuffer {
public:
  Framebuffer();

  friend std::ostream& operator<<(std::ostream& os, Framebuffer fb);

  // index from (0, 0) at bottom-left
  char &ColorAt(int x, int y);
  float &DepthAt(int x, int y);

private:
  char color_[WIDTH + 1][HEIGHT];
  float depth_[WIDTH][HEIGHT];
};

#endif // FRAMEBUFFER_HPP