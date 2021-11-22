#include "image/framebuffer.hpp"
#include <iostream>

Framebuffer::Framebuffer() {
  color_ = new char*[HEIGHT];
  depth_ = new float*[HEIGHT];
  for (int i = 0; i < HEIGHT; i++) {
    color_[i] = new char[WIDTH];
    depth_[i] = new float[WIDTH];
  }

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      color_[y][x] = '@';
      depth_[y][x] = std::numeric_limits<float>::max();
    }
  }
}

Framebuffer::~Framebuffer() {
  for (int i = 0; i < HEIGHT; i++) {
    delete[] color_[i];
    delete[] depth_[i];
  }

  delete[] color_;
  delete[] depth_;
}

void Framebuffer::Display() const {
  for (int row = HEIGHT - 1; row >= 0; row--) {
    for (int col = 0; col < WIDTH; col++) {
      std::cout << color_[row][col];
    } 
    std::cout << std::endl;
  }
}

char &Framebuffer::ColorAt(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    throw std::runtime_error("Framebuffer color index out of bounds");
  }

  return color_[y][x];
}

float &Framebuffer::DepthAt(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    throw std::runtime_error("Framebuffer depth index out of bounds");
  }

  return depth_[y][x];
}