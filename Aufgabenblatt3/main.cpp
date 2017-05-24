#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Sphere.h"
#include "Line.h"

#define WINDOW_WIDTH 1333
#define WINDOW_HEIGHT 1000


/*
	Parameter zum Erzeugen und Verändern von der Sonne
	BITTE NICHT VERÄNDERN!
	PS.: außer du bist lebenmüde
*/
cg::Sphere* sun = nullptr;
float sunSize = 0.8;
float sunRotationAxisX = 0;
float sunRotationAxisY = 0;
float sunRotationAxisZ = 0;
float sunRotationAxisXFactor = 0;
float sunRotationAxisYFactor = 1.0f;
float sunRotationAxisZFactor = 0;
glm::vec3 sunColor = glm::vec3(1.0f, 1.0f, 0.0f);

/*
	Parameter zum Erzeugen und Verändern von der Erde
	BITTE NICHT VERÄNDERN!
	PS.: außer du bist lebenmüde
*/
cg::Sphere* earth = nullptr;
float earthSize = 0.4;
float earthAngle = 0;
float earthAngleFactor = 0.01f;
float earthRotationAxisX = 0;
float earthRotationAxisY = 0;
float earthRotationAxisZ = 0;
float earthRotationAxisXFactor = 0;
float earthRotationAxisYFactor = 1.0f;
float earthRotationAxisZFactor = 0;
glm::vec3 earthPos = glm::vec3(3, 0, 0);
glm::vec3 earthColor = glm::vec3(0.0f, 0.0f, 1.0f);

/*
	Parameter zum Erzeugen und Verändern vom Mars
	BITTE NICHT VERÄNDERN!
	PS.: außer du bist lebenmüde
*/
cg::Sphere* mars = nullptr;
float marsSize = 0.3;
float marsAngle = 0;
float marsAngleFactor = 0.01f;
float marsRotationAxisX = 0;
float marsRotationAxisY = 0;
float marsRotationAxisZ = 25.19f;
float marsRotationAxisXFactor = 0;
float marsRotationAxisYFactor = 1.0f;
float marsRotationAxisZFactor = 0;
glm::vec3 marsPos = glm::vec3(5, 0, 0);
glm::vec3 marsColor = glm::vec3(1.0f, 0.0f, 0.0f);


cg::Line* sunLine = nullptr;
cg::Line* earthLine = nullptr;
cg::Line* marsLine = nullptr;

glm::mat4x4 view;
glm::mat4x4 projection;

float zNear = 0.1f;
float zFar = 100.0f;


/*
	Funktion zum Erstellen einer Kugel
	Angle zum Kippen und Rotieren
	Size für die Größe als Faktor
	Pos für Translation
	Color für Farbe
	BITTE NICHT VERÄNDERN!
	PS.: außer du bist lebenmüde
*/
cg::Sphere* createPlanet(float angleX, float angleY, float angleZ, float size, glm::vec3 pos, glm::vec3 color) {
	cg::Sphere* sphere = new cg::Sphere(color);
	sphere->model = glm::translate(sphere->model, pos);
	sphere->model = glm::rotate(sphere->model, angleX, glm::vec3(1.0f, 0.0f, 0.0f));
	sphere->model = glm::rotate(sphere->model, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
	sphere->model = glm::rotate(sphere->model, angleZ, glm::vec3(0.0f, 0.0f, 1.0f));
	sphere->model = glm::scale(sphere->model, glm::vec3(size));
	return sphere;
}

/*
	Funktion zum Erstellen einer Linie
	Angle zum Kippen und Rotieren
	Size für die Größe als Faktor
	Pos für Translation
	Color für Farbe
	BITTE NICHT VERÄNDERN!
	PS.: außer du bist lebenmüde
*/
cg::Line* createPlanetLine(float angleX, float angleY, float angleZ, float size, glm::vec3 pos, glm::vec3 color) {
	cg::Line* sphere = new cg::Line(color);
	sphere->model = glm::translate(sphere->model, pos);
	sphere->model = glm::rotate(sphere->model, angleX, glm::vec3(1.0f, 0.0f, 0.0f));
	sphere->model = glm::rotate(sphere->model, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
	sphere->model = glm::rotate(sphere->model, angleZ, glm::vec3(0.0f, 0.0f, 1.0f));
	sphere->model = glm::scale(sphere->model, glm::vec3(size));
	return sphere;
}

/*
	Release resources on termination.
*/
void release()
{
	delete sun;
	delete earth;
	delete mars;
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
		/*
			Erstellen von Planeten und Linien
			BITTE NICHT VERÄNDERN!
			PS.: außer du bist lebenmüde
		*/
		sunLine = createPlanetLine(glm::radians(sunRotationAxisX), glm::radians(sunRotationAxisY), glm::radians(sunRotationAxisZ), sunSize, glm::vec3(0, 0, 0), sunColor);
		earthLine = createPlanetLine(glm::radians(earthRotationAxisX), glm::radians(earthRotationAxisY), glm::radians(earthRotationAxisZ), earthSize, earthPos, earthColor);
		marsLine = createPlanetLine(glm::radians(marsRotationAxisX), glm::radians(marsRotationAxisY), glm::radians(marsRotationAxisZ), marsSize, marsPos, marsColor);
		sun = createPlanet(glm::radians(sunRotationAxisX), glm::radians(sunRotationAxisY), glm::radians(sunRotationAxisZ), sunSize, glm::vec3(0,0,0), sunColor);
		earth = createPlanet(glm::radians(earthRotationAxisX), glm::radians(earthRotationAxisY), glm::radians(earthRotationAxisZ), earthSize, earthPos, earthColor);
		mars = createPlanet(glm::radians(marsRotationAxisX), glm::radians(marsRotationAxisY), glm::radians(marsRotationAxisZ), marsSize, marsPos, marsColor);
	}
	catch (const std::exception& e)
	{
		release();
		std::cerr << e.what() << std::endl;
		return false;
	}

	//std::cout << "Use x, y, z to rotate the sphere" << std::endl;
	//std::cout << "Use + and - to scale the sphere" << std::endl;

	return true;
}

/*
 Rendering.
 */
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
		Translation vom Erde + Linie
		BITTE NICHT VERÄNDERN!
		PS.: außer du bist lebenmüde
	*/
	earth->render(view, projection);
	earthLine->render(view, projection);
	float earthFactor = earthPos[0] * 1 / earthSize;
	earth->model = glm::rotate(earth->model, glm::radians(-earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	earth->model = glm::translate(earth->model, glm::vec3(-cos(earthAngle) * earthFactor, 0, -sin(earthAngle) * earthFactor));
	earthLine->model = glm::translate(earthLine->model, glm::vec3(-cos(earthAngle) * earthFactor, 0, -sin(earthAngle) * earthFactor));
	earthAngle += earthAngleFactor;
	earthRotationAxisY += earthRotationAxisYFactor;
	earth->model = glm::translate(earth->model, glm::vec3(cos(earthAngle) * earthFactor, 0, sin(earthAngle) * earthFactor));
	earth->model = glm::rotate(earth->model, glm::radians(earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	earthLine->model = glm::translate(earthLine->model, glm::vec3(cos(earthAngle) * earthFactor, 0, sin(earthAngle) * earthFactor));

	/*
		Translation vom Mars + Linie
		BITTE NICHT VERÄNDERN!
		PS.: außer du bist lebenmüde
	*/
	mars->render(view, projection);
	marsLine->render(view, projection);
	float marsFactor = marsPos[0] * 1 / marsSize;
	mars->model = glm::rotate(mars->model, glm::radians(-marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	mars->model = glm::rotate(mars->model, glm::radians(-marsRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	mars->model = glm::translate(mars->model, glm::vec3(-cos(marsAngle) * marsFactor, 0, -sin(marsAngle) * marsFactor));
	marsLine->model = glm::rotate(marsLine->model, glm::radians(-marsRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	marsLine->model = glm::translate(marsLine->model, glm::vec3(-cos(marsAngle) * marsFactor, 0, -sin(marsAngle) * marsFactor));
	marsAngle += marsAngleFactor;
	marsRotationAxisY += marsRotationAxisYFactor;
	mars->model = glm::translate(mars->model, glm::vec3(cos(marsAngle) * marsFactor, 0, sin(marsAngle) * marsFactor));
	mars->model = glm::rotate(mars->model, glm::radians(marsRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	mars->model = glm::rotate(mars->model, glm::radians(marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	marsLine->model = glm::translate(marsLine->model, glm::vec3(cos(marsAngle) * marsFactor, 0, sin(marsAngle) * marsFactor));
	marsLine->model = glm::rotate(marsLine->model, glm::radians(marsRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	
	/*
		Translation vom Sonne + Linie
		BITTE NICHT VERÄNDERN!
		PS.: außer du bist lebenmüde
	*/
	sun->render(view, projection);
	sunLine->render(view, projection);
	sun->model = glm::rotate(sun->model, glm::radians(-sunRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	sun->model = glm::rotate(sun->model, glm::radians(-sunRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	sunLine->model = glm::rotate(sunLine->model, glm::radians(-sunRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	sunLine->model = glm::rotate(sunLine->model, glm::radians(-sunRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	sunRotationAxisY += sunRotationAxisYFactor;
	sunRotationAxisZ += sunRotationAxisZFactor;
	sun->model = glm::rotate(sun->model, glm::radians(sunRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	sun->model = glm::rotate(sun->model, glm::radians(sunRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	sunLine->model = glm::rotate(sunLine->model, glm::radians(sunRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	sunLine->model = glm::rotate(sunLine->model, glm::radians(sunRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));

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
	case '+':
		break;
	case '-':
		break;
	case 'x':
		break;
	case 'X':
		break;
	case 'y':
		break;
	case 'Y':
		break;
	case 'z':
		break;
	case 'Z':
		break;
	}
}

int main(int argc, char** argv)
{
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

