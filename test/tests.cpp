#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <filesystem>

#include "image/camera.hpp"
#include "renderer.hpp"

#define EPSILON 0.001

bool CompareVectors(const glm::vec3& v1, const glm::vec3& v2) {
    return glm::all(glm::lessThan(v1 - v2, glm::vec3{EPSILON}));
}

bool CompareMatrices(const glm::mat4& m1, const glm::mat4& m2) {
    auto* m1_ptr = glm::value_ptr(m1);
    auto* m2_ptr = glm::value_ptr(m2);
    for (size_t i = 0; i < 16; i++) {
        if (abs(m1_ptr[i] - m2_ptr[i]) > EPSILON) {
            return false;
        }
    }

    return true;
}

TEST_CASE("Camera", "[camera]") {
    Camera camera{};

    SECTION("Translations") {
        // default
        REQUIRE(CompareVectors(camera.GetPosition(), glm::vec3{0, 0, 0}));

        // translate along x, y, z
        camera.TranslateX(0.5);
        REQUIRE(CompareVectors(camera.GetPosition(), glm::vec3{0.5, 0, 0}));

        camera.TranslateY(1);
        REQUIRE(CompareVectors(camera.GetPosition(), glm::vec3{0.5, 1, 0}));

        camera.TranslateZ(-0.3);
        REQUIRE(CompareVectors(camera.GetPosition(), glm::vec3{0.5, 1, -0.3}));
    }

    SECTION("View Matrix") {
        // default
        glm::mat4 default_view = glm::lookAt(glm::vec3{0}, glm::vec3{0, 0, 1}, glm::vec3{0, 1, 0});
        REQUIRE(CompareMatrices(camera.GetViewMatrix(), default_view));

        // after rotations
        camera.RotateX(90);
        camera.RotateY(30);
        glm::mat4 rotated_view = glm::lookAt(glm::vec3{0}, 
                                             glm::vec3{-cos(glm::radians(30.f)), sin(glm::radians(30.f)), 0}, 
                                             glm::vec3{-sin(glm::radians(30.f)), cos(glm::radians(30.f)), 0});
        REQUIRE(CompareMatrices(camera.GetViewMatrix(), rotated_view));
    }
}

TEST_CASE("Framebuffer", "[framebuffer]") {
    Framebuffer buffer{};

    SECTION("Color Elements") {
        REQUIRE_THROWS(buffer.ColorAt(-1, 0));
        REQUIRE_THROWS(buffer.ColorAt(0, -1));
        REQUIRE_THROWS(buffer.ColorAt(SCREEN_WIDTH, 0));
        REQUIRE_THROWS(buffer.ColorAt(0, SCREEN_HEIGHT));

        buffer.ColorAt(0, 0) = 't';
        REQUIRE(buffer.ColorAt(0, 0) == 't');
        REQUIRE(buffer.ColorAt(1, 1) == ' ');
    }

    SECTION("Depth Elements") {
        REQUIRE_THROWS(buffer.DepthAt(-1, 0));
        REQUIRE_THROWS(buffer.DepthAt(0, -1));
        REQUIRE_THROWS(buffer.DepthAt(SCREEN_WIDTH, 0));
        REQUIRE_THROWS(buffer.DepthAt(0, SCREEN_HEIGHT));

        buffer.DepthAt(0, 0) = 1.0;
        REQUIRE(buffer.DepthAt(0, 0) == 1.0);
        REQUIRE(buffer.DepthAt(1, 1) == std::numeric_limits<float>::max());
    }
}

TEST_CASE("Model", "[model]") {
    std::filesystem::path object_path =
        std::filesystem::path(__FILE__).parent_path();
    object_path.append("test_object.obj");
    Model test{object_path.string()};

    SECTION("Vertex Extremes") {
        glm::vec3 max = test.GetMaxPosition();
        glm::vec3 min = test.GetMinPosition();
        
        REQUIRE(CompareVectors(max, glm::vec3(1.831594, 1.551779, 1.647404)));
        REQUIRE(CompareVectors(min, glm::vec3(-1.497709, -1.764663, -2.930325)));
    }

    SECTION("Triangle Vertices") {
        REQUIRE(test.GetIndexCount() == 36);

        REQUIRE(CompareVectors(test.GetVertex(0).position, glm::vec3(-1.497709, 0.652318, -0.575629)));
        REQUIRE(CompareVectors(test.GetVertex(1).position, glm::vec3(1.192631, 1.254784, 0.056117)));
        REQUIRE(CompareVectors(test.GetVertex(2).position, glm::vec3(0.087335, 1.551779, -1.542688)));
    }
}
