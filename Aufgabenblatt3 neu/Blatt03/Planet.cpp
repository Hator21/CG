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
		cg::Sphere* planet = nullptr;
		float radius;
		float distance;
		std::vector<Planet> planets;
		float angle;
		float orbitspeed;
		glm::vec3 v;
		glm::mat4x4 view;
		glm::mat4x4 projection;
	public:
		// Create a wired sphere with the given color.
		Planet(float r, float d, float o, glm::mat4x4 v, glm::mat4x4 p)
		{
			
			v = glm::vec3(1.0f, 0.0f, 1.0f);
			radius = r;
			distance = d;
			v * distance;
			angle = 0.0f;
			orbitspeed = o;
			view = v;
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

		void spawnMoons(int total, int level) {
			for (int i = 0; i < total; i++) {
				float r = radius / (level * 2);
				float d = random((radius + r), (radius + r) * 2);
				float o = random(-0.1f, 0.1f);
				planets.push_back(Planet(r, d, o));
				if (level < 2) {
					int num = int(random(0, 3));
					planets[i].spawnMoons(num, level + 1);
				}
			}
		}

		float random(float min, float max)
		{
			return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
		}
		
		void show() {
			planet = new cg::Sphere(glm::vec3(1.0f, 1.0f, 0.0f));
			glm::vec3 v2 = glm::vec3(1, 0, 1);
			glm::vec3 p = glm::cross(v, v2);
			planet->model = glm::rotate(planet->model, angle, glm::normalize(glm::vec3(p.x, p.y, p.z)));
			planet->model = glm::translate(planet->model, glm::vec3(v.x, v.y, v.z));
			planet->render(view, projection);
			if (planets.size() != 0) {
				for (int i = 0; i < planets.size(); i++) {
					planets[i].show();
				}
			}
			planet->model = glm::rotate(planet->model, -angle, glm::normalize(glm::vec3(p.x, p.y, p.z)));
			planet->model = glm::translate(planet->model, -glm::vec3(v.x, v.y, v.z));
		}
} // namespace cg

#endif // SPHERE_H