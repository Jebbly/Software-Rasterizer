#include <iostream>
#include "renderer.hpp"

int main(int argc, char *argv[]) {
  if (argc == 0) {
    std::cout << "Please provide a file path!" << std::endl;
    return -1;
  }

  Renderer *renderer = new Renderer{argv[1]};
  renderer->Run();
}