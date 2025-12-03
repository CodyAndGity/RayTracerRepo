#pragma once
#include "Color.h"
#include "Ray.h"
class Object{
public:
		Object() = default;
		Object(const color3_t& color) :color{ color } {};

		virtual bool Hit(const Ray& ray, float minDistance, float maxDistance, RayHit& raycastHit) = 0;

protected:
		color3_t color{0,0,0};
};