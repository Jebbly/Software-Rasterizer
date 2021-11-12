#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "model.hpp"
#include <iostream>
#include <string>

class Renderer {
public:
    // constructor initializes the resolution
    Renderer(size_t width, size_t height, const std::string& filepath);
    void Run();

private:
    Model model_;
    size_t width_, height_;
    bool close_;

    void ProcessInput();
    void Draw();
};

#endif // RENDERER_HPP