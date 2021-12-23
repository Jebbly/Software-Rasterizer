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

  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
      color_[y][x] = ' ';
      depth_[y][x] = std::numeric_limits<float>::max();
    }
  }

  // by setting additional characters
  // the buffer can be printed all at once
  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    color_[y][SCREEN_WIDTH] = '\n';
  }

  color_[SCREEN_HEIGHT - 1][SCREEN_WIDTH] = '\0';
}

void Framebuffer::Display() const {
  std::cout << color_[0];
}

void Framebuffer::Clear() {
  // clear color is a space character
  // depth should be set to the maximum possible value
  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
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
  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
    throw std::runtime_error("Framebuffer color index out of bounds!");
  }

  return color_[SCREEN_HEIGHT - 1 - y][x];
}

float &Framebuffer::DepthAt(int x, int y) {
  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
    throw std::runtime_error("Framebuffer depth index out of bounds");
  }

  return depth_[SCREEN_HEIGHT - 1 - y][x];
}