#pragma once
#include <glm/glm.hpp>
#include "Color.h"
struct Ray {
public:
	Ray() {}

	Ray(const glm::vec3& origin, const glm::vec3& direction) :
		origin(origin), direction(direction) {
	}

	const glm::vec3& getOrigin() const { return origin; }
	const glm::vec3& getDirection() const { return direction; }

	glm::vec3 at(float time) const {
		return origin + direction*time;
	}
	glm::vec3 operator * (float time) const {
		return at(time);
	}

public:
	glm::vec3 origin{ 0,0,0 };
	glm::vec3 direction{ 1,0,0 };
};

struct RayHit {
	glm::vec3 point{ 0,0,0 };
	glm::vec3 normal{ 0,0,0 };
	float distance{ 0.0f };
	color3_t color{ 0,0,1 };
};