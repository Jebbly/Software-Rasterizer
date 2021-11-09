#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <glm/vec2.hpp>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Please provide a file path!" << std::endl;
        return -1;
    }

    glm::vec2 test{1.0, 0.5};
    std::cout << "Test GLM Vector: (" << test.x << ", " << test.y << ')' << std::endl;
}