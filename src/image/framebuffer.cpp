#include "image/framebuffer.hpp"

Framebuffer::Framebuffer() {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      color_[y][x] = ' ';
      depth_[y][x] = std::numeric_limits<float>::max();
    }
  }
}

void Framebuffer::Display() const {
  // TO-DO: implement display method for framebuffer
}

char &Framebuffer::ColorAt(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y > HEIGHT) {
    throw std::runtime_error("Framebuffer color index out of bounds!");
  }

  return color_[y][x];
}

float &Framebuffer::DepthAt(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y > HEIGHT) {
    throw std::runtime_error("Framebuffer depth index out of bounds!");
  }

  return depth_[y][x];
}