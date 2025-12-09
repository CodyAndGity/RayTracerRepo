#include <iostream>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include "Renderer.h"
#include "Framebuffer.h"
#include "Ray.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Random.h"
#include "Object.h"
#include "Plane.h"
int main() {
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;

	// create renderer
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", SCREEN_WIDTH, SCREEN_HEIGHT);

	Framebuffer framebuffer(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	float aspectRatio = framebuffer.width / (float)framebuffer.height;
	Camera camera(20.0f, aspectRatio);
	camera.SetView({ 13, 2,  3 }, { 0, 0, 0 });

	Scene scene; // after camera creation/initialization
	scene.SetSky({ 1,1,1 }, { 1,1,1 });
	auto ground_material = std::make_shared<Lambertian>(color3_t(0.5f, 0.5f, 0.5f));
scene.AddObject(std::make_unique<Plane>(Transform{ { 0.0f, 0.0f, 0.0f } }, ground_material));

for (int a = -11; a < 11; a++) {
	for (int b = -11; b < 11; b++) {
		glm::vec3 position(a + 0.9f * random::getReal(), 0.2f, b + 0.9f * random::getReal());

		if ((position - glm::vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
			std::shared_ptr<Material> sphere_material;

			auto choose_mat = random::getReal();
			if (choose_mat < 0.8f) {
				// diffuse
				auto albedo = HSVtoRGB({ 360.0f * random::getReal(), 1.0f, 1.0f });
				sphere_material = std::make_shared<Lambertian>(albedo);
				scene.AddObject(std::make_unique<Sphere>(Transform{ position }, 0.2f, sphere_material));
			}
			else if (choose_mat < 0.87f) {
				// metal
				auto albedo = color3_t{ random::getReal(0.5f, 1.0f) };
				auto fuzz = random::getReal(0.5f);
				sphere_material = std::make_shared<Metal>(albedo, fuzz);
				scene.AddObject(std::make_unique<Sphere>(Transform{ position }, 0.2f, sphere_material));
			}
			else if (choose_mat < 0.93f) {
				// Emissive
				auto albedo = HSVtoRGB({ 360.0f * random::getReal(), 1.0f, 1.0f });

				auto intensity = random::getReal(5.0f, 10.0f);
				sphere_material = std::make_shared<Emissive>(albedo, intensity);
				scene.AddObject(std::make_unique<Sphere>(Transform{ position }, 0.2f, sphere_material));
			}
			else {
				// glass
				sphere_material = std::make_shared<Dielectric>(HSVtoRGB(360.0f * random::getReal(), 1.0f, 1.0f), 1.0f);
				scene.AddObject(std::make_unique<Sphere>(Transform{ position }, 0.2f, sphere_material));
			}
		}
	}
}

auto material1 = std::make_shared<Dielectric>(color3_t{ 1.0f, 1.0f, 1.0f }, 1.5f);
scene.AddObject(make_unique<Sphere>(Transform{ glm::vec3{ 0.0f, 1.0f, 0.0f } }, 1.0f, material1));

auto material2 = std::make_shared<Lambertian>(color3_t(0.4f, 0.2f, 0.1f));
scene.AddObject(make_unique<Sphere>(Transform{ glm::vec3{ -4.0f, 1.0f, 0.0f } }, 1.0f, material2));

auto material3 = std::make_shared<Metal>(color3_t(0.7f, 0.6f, 0.5f), 0.0f);
scene.AddObject(make_unique<Sphere>(Transform{ glm::vec3{ 4.0f, 1.0f, 0.0f } }, 1.0f, material3));
	/*
	auto red = std::make_shared<Lambertian>(color3_t{ 1.0f, 0.0f, 0.0f });
	auto green = std::make_shared<Lambertian>(color3_t{ 0.0f, 1.0f, 0.0f });//<green lambertian>
	auto blue = std::make_shared<Lambertian>(color3_t{ 0.0f, 0.0f, 1.0f });// <blue lambertian>
	auto light = std::make_shared<Emissive>(color3_t{ 1.0f, 1.0f, 1.0f }, 3.0f);
	auto metal = std::make_shared<Metal>(color3_t{ 1.0f, 1.0f, 1.0f }, 0.0f);
	auto dielectric = std::make_shared<Dielectric>(color3_t{ 1.0f, 1.0f, 1.0f }, 1.3f);
	std::shared_ptr<Material> materials[6] = { red, green, blue, light, metal,dielectric };

	std::vector<Transform> positions;
	bool positionValid = true;

	auto snow = std::make_shared<Lambertian>(color3_t{ 1.0f, 1.0f, 1.0f });
	for (int i = 0; i < 3; i++) {
		float radius = 0.6f - (0.1f * i);
		//need prior radius to offset y position
		Transform transform = Transform{ glm::vec3{ -6.0f, radius + i, -3.0f } };
		positions.push_back(transform);

		std::unique_ptr<Object> sphere = std::make_unique<Sphere>(transform, radius , snow);
		scene.AddObject(std::move(sphere));
	}

	for (int i = 0; i < 50; i++) {
		float radius = random::getReal(0.2f, 0.6f);
		glm::vec3 newPosition = random::getReal(glm::vec3{ -7.0f, radius, -4.0f }, glm::vec3{ 7.0f, radius, 4.0f });
		for (auto& position : positions) {
			if (glm::length(position.position - newPosition) < radius + 0.5f) {
				positionValid = false;
				//newPosition = random::getReal(glm::vec3{ -3.0f, radius, -3.0f }, glm::vec3{ 3.0f, radius, 3.0f });
			}
		}
		if (!positionValid) {
			if (random::getBool()) {
				continue;
			}
		}

		Transform transform = Transform{ newPosition };
		positions.push_back(transform);
		std::unique_ptr<Object> sphere = std::make_unique<Sphere>(transform, radius, materials[random::getInt(6)]);
		scene.AddObject(std::move(sphere));
	}
	// place plane in scene with gray material
	auto gray = std::make_shared<Lambertian>(color3_t{ 0.2f, 0.2f, 0.2f });
	std::unique_ptr<Plane> plane = std::make_unique<Plane>(Transform{ glm::vec3{ 0.0f, 0.0f, 0.0f } }, gray);
	scene.AddObject(std::move(plane));
	*/
	SDL_Event event;
	bool quit = false;
	while (!quit) {
		// check for exit events
		while (SDL_PollEvent(&event)) {
			// window (X) quit
			if (event.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			// escape key quit
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
				quit = true;
			}
		}

		// draw to frame buffer
		framebuffer.Clear({ 0, 0, 0, 255 });

		scene.Render(framebuffer, camera, 200);

		// update frame buffer, copy buffer pixels to texture
		framebuffer.Update();


		// copy frame buffer texture to renderer to display
		renderer.CopyFramebuffer(framebuffer);
		renderer.Show();
	}
}