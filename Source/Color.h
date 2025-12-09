#pragma once
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <algorithm>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/color_space.hpp>
// use alias to clarify type name
using color3_t = glm::vec3;
using color4_t = glm::vec4;

inline color3_t HSVtoRGB(const color3_t& hsv)
{
	return glm::rgbColor(hsv);
}

inline color3_t HSVtoRGB(float hue, float saturation, float value)
{
	return glm::rgbColor(glm::vec3{ hue, saturation, value });
}
inline float LinearToGamma(float linear) {
	return (linear > 0) ? std::sqrt(linear) : 0;
}
// convert from RGBA(0.0 - 1.0) color to (0 - 255) color
inline SDL_Color ColorConvert(const color4_t& color4)
{
	SDL_Color color;

	color.r = (uint8_t)(std::clamp(LinearToGamma(color4.r), 0.0f, 1.0f) * 255);
	color.g = (uint8_t)(std::clamp(LinearToGamma(color4.g), 0.0f, 1.0f) * 255);
	color.b = (uint8_t)(std::clamp(LinearToGamma(color4.b), 0.0f, 1.0f) * 255);
	color.a = (uint8_t)(std::clamp((color4.a), 0.0f, 1.0f) * 255);

	return color;
}

// convert from RGB(0.0 - 1.0) color to (0 - 255) color
inline SDL_Color ColorConvert(const color3_t& color3)
{
	SDL_Color color;

	color.r = (uint8_t)(std::clamp(LinearToGamma(color3.r), 0.0f, 1.0f) * 255);
	color.g = (uint8_t)(std::clamp(LinearToGamma(color3.g), 0.0f, 1.0f) * 255);
	color.b = (uint8_t)(std::clamp(LinearToGamma(color3.b), 0.0f, 1.0f) * 255);
	color.a = 255;

	return color;
}

// convert from (0 - 255) color to RGBA(0.0 - 1.0) color
inline color4_t ColorConvert(const SDL_Color& color)
{
	color4_t color4;

	color4.r = color.r / 255.0f; // convert SDL_Color color to color4
	color4.g = color.g / 255.0f; // convert SDL_Color color to color4
	color4.b = color.b / 255.0f; // convert SDL_Color color to color4
	color4.a = color.a / 255.0f; // convert SDL_Color color to color4

	return color4;
}
