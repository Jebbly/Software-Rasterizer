#include "image/framebuffer.hpp"
#include <iostream>

Framebuffer::Framebuffer() {
  for (int y = 0; y < HEIGHT; y++) {
    int h = HEIGHT - 1 - y;
    for (int x = 0; x < WIDTH + 1; x++) {
      if (x == WIDTH) {
        color_[h][x] = '\n';
        continue;
      }
      color_[h][x] = ' ';
      depth_[h][x] = std::numeric_limits<float>::max();
    }
  }
  color_[HEIGHT - 1][WIDTH] = '\0';
}

std::ostream& operator<<(std::ostream& os, Framebuffer fb) {
  os << fb.color_[0];
  return os;
}

char &Framebuffer::ColorAt(int x, int y) {
  if (x < 0 || x >= WIDTH * HEIGHT) {
    throw std::runtime_error("Framebuffer color index out of bounds!");
  }
  int h = HEIGHT - 1 - y;
  return color_[h][x];
}

float &Framebuffer::DepthAt(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    throw std::runtime_error("Framebuffer depth index out of bounds");
  }
  int h = HEIGHT - 1 - y;

  return depth_[h][x];
}