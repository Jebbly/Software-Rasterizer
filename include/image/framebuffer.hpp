#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "geometry/vertex.hpp"
#include <limits>
#include <stdexcept>
#include <stdlib.h>
#include <iostream>

constexpr int CHARACTER_WIDTH = 8;
constexpr int CHARACTER_HEIGHT = 12;
constexpr float CHARACTER_ASPECT_RATIO = ((float) CHARACTER_HEIGHT) / CHARACTER_WIDTH;

constexpr int WIDTH = 1200 / CHARACTER_WIDTH;
constexpr int HEIGHT = 600 / CHARACTER_HEIGHT;

class Framebuffer {
public:
  Framebuffer();
  ~Framebuffer();

  void Display() const;

  // index from (0, 0) at bottom-left
  char &ColorAt(int x, int y);
  float &DepthAt(int x, int y);

private:
  char** color_;
  float** depth_;
};

#endif // FRAMEBUFFER_HPP