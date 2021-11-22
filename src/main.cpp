#include <iostream>

#include <glm/vec2.hpp>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "renderer.hpp"

int main(int argc, char *argv[]) {
  if (argc == 0) {
    std::cout << "Please provide a file path!" << std::endl;
    return -1;
  }

  Renderer *renderer = new Renderer{"test"};
  renderer->Run();
}