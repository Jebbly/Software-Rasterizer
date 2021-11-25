#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "image/camera.hpp"
#include "renderer.hpp"

TEST_CASE("Camera", "[camera]") {
    Camera camera{};

    SECTION("Transformations") {
        // default
        REQUIRE(camera.GetPosition() == glm::vec3{0, 0, 0});

        camera.TranslateX(0.5);
        REQUIRE(camera.GetPosition() == glm::vec3{0.5, 0, 0});


    }

    SECTION("Directional Vectors") {
        // default
        // REQUIRE(camera.GetFront() == glm::vec3(0, 0, 1.0));

    }

    SECTION("View Matrix") {

    }
}

TEST_CASE("Framebuffer", "[framebuffer]") {
    REQUIRE(true);
}

TEST_CASE("Model", "[model]") {
    REQUIRE(true);
}

TEST_CASE("Renderer", "[renderer]") {
    Renderer renderer{"test"};
    SECTION("Edge Function") {
        glm::vec3 v1{0, 1, 5};
        glm::vec3 v2{1, -1, 10};
        glm::vec3 v3{-1, -1, -3};
        glm::vec2 p{0, 0};

        // REQUIRE(renderer.EdgeFunction(v1, v2, p) == 1.0);
        // REQUIRE(renderer.EdgeFunction(v2, v3, p) == 2.0);
        // REQUIRE(renderer.EdgeFunction(v3, v1, p) == 1.0);
    }
}