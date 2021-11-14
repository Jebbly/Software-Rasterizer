#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "camera.hpp"
#include "model.hpp"
#include <iostream>
#include <string>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

class Renderer {
public:
    // constructor initializes the resolution
    Renderer(const std::string& filepath);
    void Run();

private:
    Model model_;
    Camera camera_;
    bool close_;

    const float translation_speed_ = 1.0;
    const float rotation_speed_ = 1.0;

    void ProcessInput();
    void Draw();
};

#endif // RENDERER_HPP