#pragma once
#include "Object.h"
#include "Material.h"
#include <memory>
#include <memory.h>
class Sphere : public Object{
public:
	Sphere() = default;
	Sphere(const Transform& transform,  float radius, std::shared_ptr<Material> material) :
		Object(transform, material),
		
		radius{ radius } {  };

	bool Hit(const Ray& ray, float minDistance, float maxDistance, RayHit& raycastHit) override;

public:
	
	float radius{ 0 };
};