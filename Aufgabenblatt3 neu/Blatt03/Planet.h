#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLSLProgram.h"
#include "Object.h"

#include "Sphere.h"

namespace cg
{
	class Planet
	{
	public:
		cg::Sphere* planet = nullptr;
		float radius;
		float size;
		std::vector<Planet> planets;
		float angle;
		float orbitspeed;
		glm::mat4x4 view;
		glm::mat4x4 projection;

		// Create a wired sphere with the given color.
		cg::Sphere* getSphere() const { return planet; }
		cg::Planet* getPlanet(int index) { return &planets[index]; }
		float getSize() const { return size; }

		Planet( float r, float a, float s, float o, glm::vec3 color, glm::mat4x4 vi, glm::mat4x4 p) {
			planet = new cg::Sphere(color);
			radius = r;
			size = s;
			angle = a;
			orbitspeed = o;
			view = vi;
			projection = p;
		}

		void orbit() {
			angle = angle + orbitspeed;
			if (planets.size() != 0) {
				for (int i = 0; i < planets.size(); i++) {
					planets[i].orbit();
				}
			}
		}

		void spawnMoons() {
			planets.push_back(Planet(3,  0, 0.5f, 0.5, glm::vec3(0, 0, 1), view, projection));
			planets.push_back(Planet(6, 180, 0.4f, 0.5, glm::vec3(1, 0, 0), view, projection));
			planets.push_back(Planet(1, 0, 0.1f, 2, glm::vec3(1, 1, 1), view, projection));
			planets.push_back(Planet(1, 120, 0.1f, 2, glm::vec3(1, 1, 1), view, projection));
			planets.push_back(Planet(1, 240, 0.1f, 2, glm::vec3(1, 1, 1), view, projection));
			planets.push_back(Planet(1, 0, 0.1f, 2, glm::vec3(1, 1, 1), view, projection));
			planets.push_back(Planet(1, 90, 0.1f, 2, glm::vec3(1, 1, 1), view, projection));
			planets.push_back(Planet(1, 180, 0.1f, 2, glm::vec3(1, 1, 1), view, projection));
			planets.push_back(Planet(1, 270, 0.1f, 2, glm::vec3(1, 1, 1), view, projection));

		}

		float random(float min, float max) {
			return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
		}

		void show(glm::mat4x4 vi, glm::mat4x4 p) {
			getSphere()->render(vi, p);
			if (planets.size() != 0) {
				for (int i = 0; i < planets.size(); i++) {
					planets[i].show(vi, p);
				}
			}
		}
	};
} 

#endif 