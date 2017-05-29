#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Sphere.h"
#include "Planet.h"
#include "Line.h"

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 1080

cg::Planet* sun = nullptr;
cg::Sphere* sphere = nullptr;
float rotationSpeed = 0.01f;
float earthangle = 0;
float marsangle = 0;
float marsZAngle = 45;

cg::Line* sunLine = nullptr;
cg::Line* earthLine = nullptr;
cg::Line* marsLine = nullptr;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;

/*
Release resources on termination.
*/
void release()
{
	delete sun;
	delete sunLine;
	delete earthLine;
	delete marsLine;
}

/*
 Initialization. Should return true if everything is ok and false if something went wrong.
 */
bool init()
{
	// OpenGL stuff. Set "background" color and enable depth testing.
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Width of the lines.
	glLineWidth(1.0f);

	// Construct view matrix.
	glm::vec3 eye(0.0f, 0.0f, 8.0f);
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 up(0.0f, 2.0f, 0.0f);

	view = glm::lookAt(eye, center, up);

	// Create pyramid object.
	try
	{
		sun = new cg::Planet(0, 0, 1, 0, glm::vec3(1, 1, 0), view, projection);

		sunLine = new cg::Line(glm::vec3(1, 1, 1));
		earthLine = new cg::Line(glm::vec3(1, 1, 1));
		marsLine = new cg::Line(glm::vec3(1, 1, 1));

		sun->spawnMoons();
	}
	catch (const std::exception& e)
	{
		release();
		std::cerr << e.what() << std::endl;
		return false;
	}

	std::cout << "Use x, y, z to rotate the sphere" << std::endl;
	std::cout << "Use + and - to scale the sphere" << std::endl;

	return true;
}


void translateSphere(cg::Planet* p, glm::vec3 vecT) {
	p->getSphere()->model = glm::translate(p->getSphere()->model, vecT);
}
void rotateSphere(cg::Planet* p, float angle, glm::vec3 vecR) {
	p->getSphere()->model = glm::rotate(p->getSphere()->model, angle, vecR);
}
void scaleSphere(cg::Planet* p, glm::vec3 vecS) {
	p->getSphere()->model = glm::scale(p->getSphere()->model, vecS);
}

void translateLine(cg::Line* p, glm::vec3 vecT) {
	p->model = glm::translate(p->model, vecT);
}
void rotateLine(cg::Line* p, float angle, glm::vec3 vecR) {
	p->model = glm::rotate(p->model, angle, vecR);
}
void scaleLine(cg::Line* p, glm::vec3 vecS) {
	p->model = glm::scale(p->model, vecS);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	rotateSphere(sun, rotationSpeed, glm::normalize(glm::vec3(0, 1, 0)));
	rotateLine(sunLine, rotationSpeed, glm::normalize(glm::vec3(0, 1, 0)));

	translateSphere(&sun->planets[0], glm::vec3(
		cos(glm::radians(sun->planets[0].angle))*sun->planets[0].radius,
		0,
		sin(glm::radians(sun->planets[0].angle))*sun->planets[0].radius
	));
	translateLine(earthLine, glm::vec3(
		cos(glm::radians(sun->planets[0].angle))*sun->planets[0].radius,
		0,
		sin(glm::radians(sun->planets[0].angle))*sun->planets[0].radius
	));

	translateSphere(&sun->planets[1], glm::vec3(
		cos(glm::radians(sun->planets[1].angle))*sun->planets[1].radius,
		0,
		sin(glm::radians(sun->planets[1].angle))*sun->planets[1].radius
	));
	translateLine(marsLine, glm::vec3(
		cos(glm::radians(sun->planets[1].angle))*sun->planets[1].radius,
		0,
		sin(glm::radians(sun->planets[1].angle))*sun->planets[1].radius
	));

	translateSphere(&sun->planets[2], glm::vec3(
		cos(glm::radians(sun->planets[2].angle))*sun->planets[2].radius
		+ cos(glm::radians(sun->planets[0].angle))*sun->planets[0].radius,
		0,
		sin(glm::radians(sun->planets[2].angle))*sun->planets[2].radius
		+ sin(glm::radians(sun->planets[0].angle))*sun->planets[0].radius)
	);
	
	translateSphere(&sun->planets[3], glm::vec3(
		cos(glm::radians(sun->planets[3].angle))*sun->planets[3].radius
		+ cos(glm::radians(sun->planets[0].angle))*sun->planets[0].radius,
		0,
		sin(glm::radians(sun->planets[3].angle))*sun->planets[3].radius
		+ sin(glm::radians(sun->planets[0].angle))*sun->planets[0].radius)
	);

	translateSphere(&sun->planets[4], glm::vec3(
		cos(glm::radians(sun->planets[4].angle))*sun->planets[4].radius
		+ cos(glm::radians(sun->planets[0].angle))*sun->planets[0].radius,
		0,
		sin(glm::radians(sun->planets[4].angle))*sun->planets[4].radius
		+ sin(glm::radians(sun->planets[0].angle))*sun->planets[0].radius)
	);
	translateSphere(&sun->planets[5], glm::vec3(
		cos(glm::radians(sun->planets[5].angle))*sun->planets[5].radius
		+ cos(glm::radians(sun->planets[1].angle))*sun->planets[1].radius,
		0,
		sin(glm::radians(sun->planets[5].angle))*sun->planets[5].radius
		+ sin(glm::radians(sun->planets[1].angle))*sun->planets[1].radius)
	);

	translateSphere(&sun->planets[6], glm::vec3(
		cos(glm::radians(sun->planets[6].angle))*sun->planets[6].radius
		+ cos(glm::radians(sun->planets[1].angle))*sun->planets[1].radius,
		0,
		sin(glm::radians(sun->planets[6].angle))*sun->planets[6].radius
		+ sin(glm::radians(sun->planets[1].angle))*sun->planets[1].radius)
	);

	translateSphere(&sun->planets[7], glm::vec3(
		cos(glm::radians(sun->planets[7].angle))*sun->planets[7].radius
		+ cos(glm::radians(sun->planets[1].angle))*sun->planets[1].radius,
		0,
		sin(glm::radians(sun->planets[7].angle))*sun->planets[7].radius
		+ sin(glm::radians(sun->planets[1].angle))*sun->planets[1].radius)
	);

	translateSphere(&sun->planets[8], glm::vec3(
		cos(glm::radians(sun->planets[8].angle))*sun->planets[8].radius
		+ cos(glm::radians(sun->planets[1].angle))*sun->planets[1].radius,
		0,
		sin(glm::radians(sun->planets[8].angle))*sun->planets[8].radius
		+ sin(glm::radians(sun->planets[1].angle))*sun->planets[1].radius)
	);

	rotateSphere(&sun->planets[0], earthangle, glm::normalize(glm::vec3(0, 1, 0)));
	rotateLine(earthLine, earthangle, glm::normalize(glm::vec3(0, 1, 0)));
	rotateSphere(&sun->planets[1], marsZAngle, glm::normalize(glm::vec3(0, 0, 1)));
	rotateLine(marsLine, marsZAngle, glm::normalize(glm::vec3(0, 0, 1)));
	rotateSphere(&sun->planets[1], marsangle, glm::normalize(glm::vec3(0, 1, 0)));
	rotateLine(marsLine, marsangle, glm::normalize(glm::vec3(0, 1, 0)));
	rotateSphere(&sun->planets[5], marsZAngle, glm::normalize(glm::vec3(0, 0, 1)));
	rotateSphere(&sun->planets[6], marsZAngle, glm::normalize(glm::vec3(0, 0, 1)));
	rotateSphere(&sun->planets[7], marsZAngle, glm::normalize(glm::vec3(0, 0, 1)));
	rotateSphere(&sun->planets[8], marsZAngle, glm::normalize(glm::vec3(0, 0, 1)));

	for (int i = 0; i < 9; i++) {
		scaleSphere(&sun->planets[i], glm::vec3(sun->planets[i].getSize()));
	}
	
	sun->show(view, projection);
	sunLine->render(view, projection);
	earthLine->render(view, projection);
	marsLine->render(view, projection);

	for (int i = 0; i < 9; i++) {
		scaleSphere(&sun->planets[i], glm::vec3(1 / sun->planets[i].getSize()));
	}

	rotateSphere(&sun->planets[0], -earthangle, glm::normalize(glm::vec3(0, 1, 0)));
	rotateLine(earthLine, -earthangle, glm::normalize(glm::vec3(0, 1, 0)));
	rotateSphere(&sun->planets[1], -marsangle, glm::normalize(glm::vec3(0, 1, 0)));
	rotateLine(marsLine, -marsangle, glm::normalize(glm::vec3(0, 1, 0)));
	rotateSphere(&sun->planets[1], -marsZAngle, glm::normalize(glm::vec3(0, 0, 1)));
	rotateLine(marsLine, -marsZAngle, glm::normalize(glm::vec3(0, 0, 1)));
	rotateSphere(&sun->planets[5], -marsZAngle, glm::normalize(glm::vec3(0, 0, 1)));
	rotateSphere(&sun->planets[6], -marsZAngle, glm::normalize(glm::vec3(0, 0, 1)));
	rotateSphere(&sun->planets[7], -marsZAngle, glm::normalize(glm::vec3(0, 0, 1)));
	rotateSphere(&sun->planets[8], -marsZAngle, glm::normalize(glm::vec3(0, 0, 1)));
	
	translateSphere(&sun->planets[0], glm::vec3(
		-cos(glm::radians(sun->planets[0].angle))*sun->planets[0].radius,
		0,
		-sin(glm::radians(sun->planets[0].angle))*sun->planets[0].radius
	));
	translateLine(earthLine, glm::vec3(
		-cos(glm::radians(sun->planets[0].angle))*sun->planets[0].radius,
		0,
		-sin(glm::radians(sun->planets[0].angle))*sun->planets[0].radius
	));

	translateSphere(&sun->planets[1], glm::vec3(
		-cos(glm::radians(sun->planets[1].angle))*sun->planets[1].radius,
		0,
		-sin(glm::radians(sun->planets[1].angle))*sun->planets[1].radius
	));
	translateLine(marsLine, glm::vec3(
		-cos(glm::radians(sun->planets[1].angle))*sun->planets[1].radius,
		0,
		-sin(glm::radians(sun->planets[1].angle))*sun->planets[1].radius
	));

	translateSphere(&sun->planets[2], glm::vec3(
		-cos(glm::radians(sun->planets[2].angle))*sun->planets[2].radius
		- cos(glm::radians(sun->planets[0].angle))*sun->planets[0].radius,
		0,
		-sin(glm::radians(sun->planets[2].angle))*sun->planets[2].radius
		- sin(glm::radians(sun->planets[0].angle))*sun->planets[0].radius)
	);

	translateSphere(&sun->planets[3], glm::vec3(
		-cos(glm::radians(sun->planets[3].angle))*sun->planets[3].radius
		- cos(glm::radians(sun->planets[0].angle))*sun->planets[0].radius,
		0,
		-sin(glm::radians(sun->planets[3].angle))*sun->planets[3].radius
		- sin(glm::radians(sun->planets[0].angle))*sun->planets[0].radius)
	);

	translateSphere(&sun->planets[4], glm::vec3(
		-cos(glm::radians(sun->planets[4].angle))*sun->planets[4].radius
		- cos(glm::radians(sun->planets[0].angle))*sun->planets[0].radius,
		0,
		-sin(glm::radians(sun->planets[4].angle))*sun->planets[4].radius
		- sin(glm::radians(sun->planets[0].angle))*sun->planets[0].radius)
	);

	translateSphere(&sun->planets[5], glm::vec3(
		-cos(glm::radians(sun->planets[5].angle))*sun->planets[5].radius
		- cos(glm::radians(sun->planets[1].angle))*sun->planets[1].radius,
		0,
		-sin(glm::radians(sun->planets[5].angle))*sun->planets[5].radius
		- sin(glm::radians(sun->planets[1].angle))*sun->planets[1].radius)
	);

	translateSphere(&sun->planets[6], glm::vec3(
		-cos(glm::radians(sun->planets[6].angle))*sun->planets[6].radius
		- cos(glm::radians(sun->planets[1].angle))*sun->planets[1].radius,
		0,
		-sin(glm::radians(sun->planets[6].angle))*sun->planets[6].radius
		- sin(glm::radians(sun->planets[1].angle))*sun->planets[1].radius)
	);

	translateSphere(&sun->planets[7], glm::vec3(
		-cos(glm::radians(sun->planets[7].angle))*sun->planets[7].radius
		- cos(glm::radians(sun->planets[1].angle))*sun->planets[1].radius,
		0,
		-sin(glm::radians(sun->planets[7].angle))*sun->planets[7].radius
		- sin(glm::radians(sun->planets[1].angle))*sun->planets[1].radius)
	);

	translateSphere(&sun->planets[8], glm::vec3(
		-cos(glm::radians(sun->planets[8].angle))*sun->planets[8].radius
		- cos(glm::radians(sun->planets[1].angle))*sun->planets[1].radius,
		0,
		-sin(glm::radians(sun->planets[8].angle))*sun->planets[8].radius
		- sin(glm::radians(sun->planets[1].angle))*sun->planets[1].radius)
	);

	sun->orbit();

	earthangle += 0.01;
	marsangle += 0.01;
}

/*
 Resize callback.
 */
void resize(GLFWwindow* window, int width, int height)
{
	height = height < 1 ? 1 : height;
	glViewport(0, 0, width, height);

	// Construct projection matrix.
	projection = glm::perspective(45.0f, (float) width / height, zNear, zFar);
}

/*
 Callback for char input.
 */
void keyboard(GLFWwindow* window, unsigned int codepoint)
{
	switch (codepoint)
	{
	case 'w':
		rotationSpeed *= 0.8f;
		for (int i = 0; i < 9; i++) {
			sun->planets[i].orbitspeed *= 0.8f;
		}
		break;
	case 'W':
		rotationSpeed *= 1.2f;
		for (int i = 0; i < 9; i++) {
			sun->planets[i].orbitspeed *= 1.2f;
		}
		break;
	case 'p':
		if (marsZAngle > 0) {
			marsZAngle -= 1/360;
		}
		break;
	case 'P':
		if (marsZAngle < 1) {
			marsZAngle += 1/360;
		}
		break;
	case 's':
		sun->getSphere()->model = glm::rotate(sun->getSphere()->model, -0.1f, glm::vec3(0, 0, 1));
		sunLine->model = glm::rotate(sunLine->model, -0.1f, glm::vec3(0, 0, 1));
		break;
	case 'S':
		sun->getSphere()->model = glm::rotate(sun->getSphere()->model, 0.1f, glm::vec3(0, 0, 1));
		sunLine->model = glm::rotate(sunLine->model, 0.1f, glm::vec3(0, 0, 1));
		break;
	}
}

int main(int argc, char** argv){
	GLFWwindow* window;

	// Initialize glfw library (window toolkit).
	if (!glfwInit())
		return -1;

	// Create a window and opengl context (version 3.3 core profile).
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Turn this on for smoother lines.
	// glfwWindowHint(GLFW_SAMPLES, 8);
	
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sphere example", nullptr, nullptr);
	
	if (!window)
	{
		glfwTerminate();
		return -2;
	}

	// Make the window's opengl context current.
	glfwMakeContextCurrent(window);

	// Load opengl extensions
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();

	if (result != GLEW_OK)
	{
		glfwTerminate();
		return -3;
	}

	// Set callbacks for resize and keyboard events.
	glfwSetWindowSizeCallback(window, resize);
	glfwSetCharCallback(window, keyboard);

	if (!init())
	{
		release();
		glfwTerminate();

		return -4;
	}

	// We have to call resize once for a proper setup.
	resize(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Loop until the user closes the window.
	while (!glfwWindowShouldClose(window))
	{
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Clean up everything on termination.
	release();
	glfwTerminate();

	return 0;
}