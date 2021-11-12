#ifndef MODEL_HPP
#define MODEL_HPP

#include <exception>
#include <glm/vec3.hpp>
#include <iostream>
#include <string>
#include <vector>

class Model {
public:
  Model(const std::string &filepath);

private:
  std::vector<glm::vec3> vertices_;
};

#endif // MODEL_HPP