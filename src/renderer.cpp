#include "renderer.hpp"

Renderer::Renderer(size_t width, size_t height, const std::string& filepath) :
    width_{width}, height_{height}, model_{filepath}, close_{false}
{}

void Renderer::Run() {
    while (!close_) {
        ProcessInput();
        Draw();
    }
}

void Renderer::ProcessInput() {
    std::cout << "Process input here" << std::endl;
}

void Renderer::Draw() {
    std::cout << "Draw here" << std::endl;
}