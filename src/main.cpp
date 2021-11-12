#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <glm/vec2.hpp>

#include "renderer.hpp"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Please provide a file path!" << std::endl;
        return -1;
    }

    Renderer renderer{800, 600, argv[1]};
    renderer.Run();
}