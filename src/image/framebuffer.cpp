#include "image/framebuffer.hpp"
#include <iostream>

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
  for (size_t row = HEIGHT - 25; row >= 0; row -= 25) {
    for (size_t col = 0; col < WIDTH; col += 25) {
      std::cout << color_[row][col];
    } 
    std::cout << std::endl;
  }
  system("cls");
}

char &Framebuffer::ColorAt(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    throw std::runtime_error("Framebuffer color index out of bounds!");
  }

  return color_[y][x];
}

float &Framebuffer::DepthAt(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    throw std::runtime_error("Framebuffer depth index out of bounds!");
  }

  return depth_[y][x];
}