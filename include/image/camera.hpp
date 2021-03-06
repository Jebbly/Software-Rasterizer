#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr float TRANSLATION_SPEED = 1.0;
constexpr float ROTATION_SPEED = 1.0;

constexpr float FILM_WIDTH = 2;
constexpr float FILM_HEIGHT = 1;
constexpr float FILM_ASPECT_RATIO = FILM_WIDTH / FILM_HEIGHT;
constexpr float FOCAL_LENGTH = 1;

class Camera {
public:
  Camera(const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f), 
         float yaw = 0, float pitch = 0);

  void RotateX(float magnitude);
  void RotateY(float magnitude);

  void TranslateX(float magnitude);
  void TranslateY(float magnitude);
  void TranslateZ(float magnitude);

  glm::mat4 GetViewMatrix() const;
  const glm::vec3& GetPosition() const;

private:
  glm::vec3 position_;
  glm::vec3 front_;
  glm::vec3 up_;
  glm::vec3 right_;

  float yaw_, pitch_;

  void ComputeDirectionalVectors();
};

#endif // CAMERA_HPP