#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include "geometry/vertex.hpp"
#include <limits>
#include <stdexcept>
#include <stdlib.h>
#include <iostream>

#if defined(_WIN32)
#define NOMINMAX
#include <Windows.h>
const std::string ESCAPE_SEQUENCE{"\x1b["};
#elif defined(__linux__)
const std::string ESCAPE_SEQUENCE{"\e["};
#endif

constexpr int CHARACTER_WIDTH = 8;
constexpr int CHARACTER_HEIGHT = 16;
constexpr float CHARACTER_ASPECT_RATIO = ((float) CHARACTER_HEIGHT) / CHARACTER_WIDTH;

constexpr int WIDTH = 3200 / CHARACTER_WIDTH;
constexpr int HEIGHT = 1600 / CHARACTER_HEIGHT;

class Framebuffer {
public:
  Framebuffer();

  // screen buffer options
  void Display() const;
  void Clear();
  void ResetScreen() const;

  // index from (0, 0) at bottom-left
  char &ColorAt(int x, int y);
  float &DepthAt(int x, int y);

private:
  char color_[HEIGHT][WIDTH + 1];
  float depth_[HEIGHT][WIDTH];
};

#endif // FRAMEBUFFER_HPP