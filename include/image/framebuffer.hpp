#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "geometry/vertex.hpp"
#include <limits>
#include <stdexcept>
#include <stdlib.h>
#include <iostream>

#define CHARACTER_WIDTH 8
#define CHARACTER_HEIGHT 20

constexpr int WIDTH = 800 / CHARACTER_WIDTH;
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