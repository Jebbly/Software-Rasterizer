#ifndef MODEL_HPP
#define MODEL_HPP

#include <glm/vec3.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

class Model {
public:
    Model(const std::string& filepath);

private:
    std::vector<glm::vec3> vertices_;
};

#endif // MODEL_HPP