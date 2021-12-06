#include "image/camera.hpp"

Camera::Camera(const glm::vec3 &position, float yaw, float pitch)
    : position_{position}, yaw_{yaw}, pitch_{std::clamp(pitch, -89.0f, 89.0f)} {
  ComputeDirectionalVectors();
}

// adding magnitude should rotate clockwise for the camera
// but yaw technically increases counter-clockwise
void Camera::RotateX(float magnitude) {
  yaw_ -= magnitude;
  ComputeDirectionalVectors();
}

void Camera::RotateY(float magnitude) {
  pitch_ = std::clamp(pitch_ + magnitude, -89.0f, 89.0f);
  ComputeDirectionalVectors();
}

void Camera::TranslateX(float magnitude) { position_ += right_ * magnitude; }

void Camera::TranslateY(float magnitude) { position_ += up_ * magnitude; }

void Camera::TranslateZ(float magnitude) { position_ += front_ * magnitude; }

glm::mat4 Camera::GetViewMatrix() const {
  return glm::lookAt(position_, position_ + front_, up_);
}

const glm::vec3& Camera::GetPosition() const {
  return position_;
}

void Camera::ComputeDirectionalVectors() {
  // find camera direction based on position and target
  float yaw = glm::radians(yaw_);
  float pitch = glm::radians(pitch_);
  front_.x = sin(yaw) * cos(pitch);
  front_.y = sin(pitch);
  front_.z = cos(yaw) * cos(pitch);
  front_ = glm::normalize(front_);

  // use arbitrary vector to cross with direction to obtain right vector
  glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);
  right_ = glm::normalize(glm::cross(front_, world_up));

  // cross right and direction to obtain up vector
  up_ = glm::cross(right_, front_);
}