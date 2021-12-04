#include "image/framebuffer.hpp"

Framebuffer::Framebuffer() {
  // escape sequences need to be enabled first
#ifdef _WIN32
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD dwMode = 0;
  GetConsoleMode(hOut, &dwMode);
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hOut, dwMode);
#endif

  ResetScreen();
  Clear();

  // by setting additional characters
  // the buffer can be printed all at once
  for (int y = 0; y < HEIGHT; y++) {
    color_[y][WIDTH] = '\n';
  }

  color_[HEIGHT - 1][WIDTH] = '\0';
}

void Framebuffer::Display() const {
  std::cout << color_[0];
}

void Framebuffer::Clear() {
  // clear color is a space character
  // depth should be set to the maximum possible value
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      color_[y][x] = ' ';
      depth_[y][x] = std::numeric_limits<float>::max();
    }
  }

  std::cout << ESCAPE_SEQUENCE + "0;0H";
}

void Framebuffer::ResetScreen() const {
  std::cout << ESCAPE_SEQUENCE + "2J";
}

char &Framebuffer::ColorAt(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    throw std::runtime_error("Framebuffer color index out of bounds!");
  }

  return color_[HEIGHT - 1 - y][x];
}

float &Framebuffer::DepthAt(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    throw std::runtime_error("Framebuffer depth index out of bounds");
  }

  return depth_[HEIGHT - 1 - y][x];
}