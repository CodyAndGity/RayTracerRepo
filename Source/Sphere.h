#pragma once
#include "Object.h"
#include "Material.h"
class Sphere : public Object{
public:
	Sphere() = default;
	Sphere(Transform& transform, std::shared_ptr<Material> material,const glm::vec3& position, float radius) :
		Object(transform, material),
		
		radius{ radius } {  };

	bool Hit(const Ray& ray, float minDistance, float maxDistance, RayHit& raycastHit) override;

public:
	
	float radius{ 0 };
};