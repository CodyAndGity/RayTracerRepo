#pragma once
#include <glm/glm.hpp>

struct Ray {
public:
    Ray() {}

    Ray(const glm::vec3& origin, const glm::vec3& direction) :
        origin(origin), direction(direction) {}

    const glm::vec3& getOrigin() const { return origin; }
    const glm::vec3& getDirection() const { return direction; }

    glm::vec3 at(float time) const {
        return origin + (time * direction);
    }
   

public:
    glm::vec3 origin{0,0,0};
    glm::vec3 direction{1,0,0};
};