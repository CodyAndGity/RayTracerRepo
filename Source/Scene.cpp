#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Color.h"
#include <iostream>

void Scene::Render(Framebuffer& framebuffer, const Camera& camera) {
	// trace ray for every framebuffer pixel
	for (int y = 0; y < framebuffer.height; y++) {
		for (int x = 0; x < framebuffer.width; x++)	{
			// set pixel (x,y) coordinates)
			glm::vec2 pixel(x, y);
			// normalize (0 <-> 1) the pixel value (pixel / { framebuffer.width, framebuffer.height }
			//pixel /= glm::vec2{ framebuffer.width, framebuffer.height };
			glm::vec2 point = pixel / glm::vec2{ framebuffer.width, framebuffer.height };
			// flip the y value (bottom = 0, top = 1)
			point.y = 1 - point.y;

			// get ray from camera
			Ray ray = camera.GetRay(point);// call GetRay() from camera
				// trace ray
			RayHit raycastHit;
			// 0 = min ray distance, 100 = max ray distance
			color3_t color = Trace(ray, 0, 100, raycastHit);
			//color3_t color=Trace(ray); // class Trace with ray;
			auto c = ColorConvert(color);
			// draw pixel (x,y) to frame buffer using color (make sure to convert color)
			framebuffer.DrawPoint(x, y, c);

		}
	}
}

color3_t Scene::Trace(const Ray& ray) {
	// draw sky colors based on the ray y position
	glm::vec3 direction = glm::normalize(ray.getDirection());
	// shift direction y from -1 <-> 1 to 0 <-> 1
	direction.y = (direction.y + 1)*0.5f;

	float t = direction.y; // (direction.y + ??) * ??
	t = glm::clamp(t, 0.0f, 1.0f);
	
	// interpolate between sky bottom (0) to sky top (1)
	// mix is the same as lerp, interpolates between values using t (0-1)
	color3_t color = glm::mix(skyBottom, skyTop, t);

	return color;
}

color3_t Scene::Trace(const Ray& ray, float minDistance, float maxDistance,
	RayHit& raycastHit) {
	bool rayHit = false;
	float closestDistance = maxDistance;
	// check if scene objects are hit by the ray
	for (auto& object : objects) {
		// when checking objects don't include objects farther than closest hit
		/*if (raycastHit.distance > closestDistance) {
			continue;
		}*/
		//(starts at max distance)
			if (object->Hit(ray, minDistance, closestDistance, raycastHit)) {
				rayHit = true;
				// set closest distance to the raycast hit distance (only hit
				//objects closer than closest distance)
				closestDistance = raycastHit.distance; // raycast hit distance;
			}
	}
	// check if ray hit object
	if (rayHit) {
		// get material color of hit object
		color3_t color = raycastHit.color;
		return color;
	}
	// draw sky colors based on the ray y position
	glm::vec3 direction = glm::normalize(ray.direction);
	// shift direction y from -1 <-> 1 to 0 <-> 1
	float t = (direction.y + 1) * 0.5f;
	// interpolate between sky bottom (0) to sky top (1)
	color3_t color = glm::mix(skyBottom, skyTop, t);
	return color;
}



void Scene::AddObject(std::unique_ptr<Object> object) {
	objects.push_back(std::move(object));
}