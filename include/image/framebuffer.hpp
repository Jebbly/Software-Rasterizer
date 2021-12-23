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
constexpr int CHARACTER_HEIGHT = 18;
constexpr float CHARACTER_ASPECT_RATIO = ((float) CHARACTER_WIDTH) / CHARACTER_HEIGHT;

// the width/height can be increased
// for terminals that support more characters
// as long as the ratio matches the camera film dimensions
constexpr int SCREEN_WIDTH = 3200 / CHARACTER_WIDTH;
constexpr int SCREEN_HEIGHT = 1600 / CHARACTER_HEIGHT;
constexpr float SCREEN_ASPECT_RATIO = ((float) SCREEN_WIDTH) / SCREEN_HEIGHT;

constexpr float NEAR_CLIPPING_PLANE = 0.1;
constexpr float FAR_CLIPPING_PLANE = 1000;

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
  char color_[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
  float depth_[SCREEN_HEIGHT][SCREEN_WIDTH];
};

#endif // FRAMEBUFFER_HPP