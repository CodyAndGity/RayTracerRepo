#include "Camera.h"

void Camera::SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) {
	this->eye = eye;

	//set the camera axis vectors(forward,right,up)

	this->forward = glm::normalize(target - eye);
	//cross with forward and dummy up vector ro mkae right
	this->right = glm::normalize(cross(this->forward, up));

	//the cross product of the right and forward vector to make true up
	this->up = glm::normalize(cross(this->right, forward));

	CalculateViewPlane();
}

Ray Camera::GetRay(const glm::vec2& uv) const {
	Ray ray;

	ray.origin = eye;
	//maps ray to screen position, removes eye to give ray direction
	ray.direction = lowerLeft + (horizontal * uv.x) + (vertical * uv.y) - eye;

	return ray;
}

void Camera::CalculateViewPlane() {
	float theta = glm::radians(fov);

	float halfHeight = tan(theta * 0.5f);
	//aspect =screenWidth/screenHeight, cancel out height to get width
	float halfWidth = halfHeight * aspectRatio;

	horizontal = right * halfWidth * 2.0f;
	vertical = up * halfHeight * 2.0f;
	//we're in the center but we want the lower left corner
	lowerLeft = eye - (horizontal * 0.5f) - (vertical * 0.5f) + forward;
	//lower left origin
}

