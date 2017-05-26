#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Sphere.h"
#include "Line.h"

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 1080


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
float earthPosX = 3;
glm::vec3 earthPos = glm::vec3(earthPosX, 0, 0);
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
float marsPosX = -5;
glm::vec3 marsPos = glm::vec3(marsPosX, 0, 0);
glm::vec3 marsColor = glm::vec3(1.0f, 0.0f, 0.0f);


cg::Sphere* moon1 = nullptr;
float moon1Size = 0.1;
float moon1Angle = 0;
float moon1AngleFactor = 0.05f;
float moon1RotationAxisX = 0;
float moon1RotationAxisY = 0;
float moon1RotationAxisZ = 0;
float moon1RotationAxisXFactor = 0;
float moon1RotationAxisYFactor = 1.0f;
float moon1RotationAxisZFactor = 0;
glm::vec3 moon1Pos = glm::vec3(1, 0, 0);
glm::vec3 moon1Color = glm::vec3(1.0f, 1.0f, 1.0f);

cg::Sphere* moon2 = nullptr;
float moon2Size = 0.1;
float moon2Angle = 0;
float moon2AngleFactor = 0.05f;
float moon2RotationAxisX = 0;
float moon2RotationAxisY = 0;
float moon2RotationAxisZ = 0;
float moon2RotationAxisXFactor = 0;
float moon2RotationAxisYFactor = 1.0f;
float moon2RotationAxisZFactor = 0;
glm::vec3 moon2Pos = glm::vec3(-1, 0, 0);
glm::vec3 moon2Color = glm::vec3(1.0f, 1.0f, 1.0f);

cg::Sphere* moon3 = nullptr;
float moon3Size = 0.1;
float moon3Angle = 0;
float moon3AngleFactor = 0.05f;
float moon3RotationAxisX = 0;
float moon3RotationAxisY = 0;
float moon3RotationAxisZ = 0;
float moon3RotationAxisXFactor = 0;
float moon3RotationAxisYFactor = 1.0f;
float moon3RotationAxisZFactor = 0;
glm::vec3 moon3Pos = glm::vec3(0, 0, 1);
glm::vec3 moon3Color = glm::vec3(1.0f, 1.0f, 1.0f);

cg::Sphere* moon4 = nullptr;
float moon4Size = 0.1;
float moon4Angle = 0;
float moon4AngleFactor = 0.05f;
float moon4RotationAxisX = 0;
float moon4RotationAxisY = 0;
float moon4RotationAxisZ = 25.19f;
float moon4RotationAxisXFactor = 0;
float moon4RotationAxisYFactor = 1.0f;
float moon4RotationAxisZFactor = 0;
glm::vec3 moon4Pos = glm::vec3(1, 0, 0);
glm::vec3 moon4Color = glm::vec3(1.0f, 1.0f, 1.0f);

cg::Sphere* moon5 = nullptr;
float moon5Size = 0.1;
float moon5Angle = 0;
float moon5AngleFactor = 0.05f;
float moon5RotationAxisX = 0;
float moon5RotationAxisY = 0;
float moon5RotationAxisZ = 0;
float moon5RotationAxisXFactor = 0;
float moon5RotationAxisYFactor = 1.0f;
float moon5RotationAxisZFactor = 0;
glm::vec3 moon5Pos = glm::vec3(-1, 0, 0);
glm::vec3 moon5Color = glm::vec3(1.0f, 1.0f, 1.0f);

cg::Sphere* moon6 = nullptr;
float moon6Size = 0.1;
float moon6Angle = 0;
float moon6AngleFactor = 0.05f;
float moon6RotationAxisX = 0;
float moon6RotationAxisY = 0;
float moon6RotationAxisZ = 0;
float moon6RotationAxisXFactor = 0;
float moon6RotationAxisYFactor = 1.0f;
float moon6RotationAxisZFactor = 0;
glm::vec3 moon6Pos = glm::vec3(0, 0, 1);
glm::vec3 moon6Color = glm::vec3(1.0f, 1.0f, 1.0f);

cg::Sphere* moon7 = nullptr;
float moon7Size = 0.1;
float moon7Angle = 0;
float moon7AngleFactor = 0.05f;
float moon7RotationAxisX = 0;
float moon7RotationAxisY = 0;
float moon7RotationAxisZ = 0;
float moon7RotationAxisXFactor = 0;
float moon7RotationAxisYFactor = 1.0f;
float moon7RotationAxisZFactor = 0;
glm::vec3 moon7Pos = glm::vec3(0, 0, -1);
glm::vec3 moon7Color = glm::vec3(1.0f, 1.0f, 1.0f);



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
	cg::Line* line = new cg::Line(color);
	line->model = glm::translate(line->model, pos);
	line->model = glm::rotate(line->model, angleX, glm::vec3(1.0f, 0.0f, 0.0f));
	line->model = glm::rotate(line->model, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
	line->model = glm::rotate(line->model, angleZ, glm::vec3(0.0f, 0.0f, 1.0f));
	line->model = glm::scale(line->model, glm::vec3(size));
	return line;
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
	delete moon1;
	delete moon2;
	delete moon3;
	delete moon4;
	delete moon5;
	delete moon6;
	delete moon7;
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
	glm::vec3 eye(0.0f, 0.0f, 10.0f);
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

		moon1 = createPlanet(glm::radians(moon1RotationAxisX), glm::radians(moon1RotationAxisY), glm::radians(moon1RotationAxisZ), moon1Size, earthPos + moon1Pos, moon1Color);
		moon2 = createPlanet(glm::radians(moon2RotationAxisX), glm::radians(moon2RotationAxisY), glm::radians(moon2RotationAxisZ), moon2Size, earthPos + moon2Pos, moon2Color);
		moon3 = createPlanet(glm::radians(moon3RotationAxisX), glm::radians(moon3RotationAxisY), glm::radians(moon3RotationAxisZ), moon3Size, earthPos + moon3Pos, moon3Color);
		moon4 = createPlanet(glm::radians(moon4RotationAxisX), glm::radians(moon4RotationAxisY), glm::radians(moon4RotationAxisZ), moon4Size, marsPos + moon4Pos, moon4Color);
		moon5 = createPlanet(glm::radians(moon5RotationAxisX), glm::radians(moon5RotationAxisY), glm::radians(moon5RotationAxisZ), moon5Size, marsPos + moon5Pos, moon5Color);
		moon6 = createPlanet(glm::radians(moon6RotationAxisX), glm::radians(moon6RotationAxisY), glm::radians(moon6RotationAxisZ), moon6Size, marsPos + moon6Pos, moon6Color);
		moon7 = createPlanet(glm::radians(moon7RotationAxisX), glm::radians(moon7RotationAxisY), glm::radians(moon7RotationAxisZ), moon7Size, marsPos + moon7Pos, moon7Color);
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
	moon1->render(view, projection);
	moon2->render(view, projection);
	moon3->render(view, projection);
	moon4->render(view, projection);
	moon5->render(view, projection);
	moon6->render(view, projection);
	moon7->render(view, projection);




	float earthFactor = earthPosX;
	earthPos = glm::vec3(-cos(earthAngle) * earthFactor, 0, -sin(earthAngle) * earthFactor);

	earth->model = glm::scale(earth->model, glm::vec3(1 / earthSize));
	earth->model = glm::rotate(earth->model, glm::radians(-earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	earth->model = glm::translate(earth->model, earthPos);

	earthLine->model = glm::scale(earthLine->model, glm::vec3(1 / earthSize));
	earthLine->model = glm::rotate(earthLine->model, glm::radians(-earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	earthLine->model = glm::translate(earthLine->model, earthPos);

	moon1->model = glm::scale(moon1->model, glm::vec3(1 / moon1Size));
	moon1->model = glm::rotate(moon1->model, glm::radians(-earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon1->model = glm::translate(moon1->model, earthPos);
	moon1->model = glm::translate(moon1->model, -moon1Pos);

	moon2->model = glm::scale(moon2->model, glm::vec3(1 / moon2Size));
	moon2->model = glm::rotate(moon2->model, glm::radians(-earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon2->model = glm::translate(moon2->model, earthPos);
	moon2->model = glm::translate(moon2->model, -moon2Pos);

	moon3->model = glm::scale(moon3->model, glm::vec3(1 / moon3Size));
	moon3->model = glm::rotate(moon3->model, glm::radians(-earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon3->model = glm::translate(moon3->model, earthPos);
	moon3->model = glm::translate(moon3->model, -moon3Pos);

	earthAngle += earthAngleFactor;
	earthRotationAxisY += earthRotationAxisYFactor;
	earthPos = glm::vec3(cos(earthAngle) * earthFactor, 0, sin(earthAngle) * earthFactor);

	moon1Angle += moon1AngleFactor;
	moon1RotationAxisY += moon1RotationAxisYFactor;

	moon1Pos = glm::vec3(moon1Pos[0] * cos(moon1AngleFactor) - moon1Pos[2] * sin(moon1AngleFactor), moon1Pos[1], moon1Pos[2] * cos(moon1AngleFactor) + moon1Pos[0] * sin(moon1AngleFactor));
	moon2Pos = glm::vec3(moon2Pos[0] * cos(moon2AngleFactor) - moon2Pos[2] * sin(moon2AngleFactor), moon2Pos[1], moon2Pos[2] * cos(moon2AngleFactor) + moon2Pos[0] * sin(moon2AngleFactor));
	moon3Pos = glm::vec3(moon3Pos[0] * cos(moon3AngleFactor) - moon3Pos[2] * sin(moon3AngleFactor), moon3Pos[1], moon3Pos[2] * cos(moon3AngleFactor) + moon3Pos[0] * sin(moon3AngleFactor));

	moon1->model = glm::translate(moon1->model, moon1Pos);
	moon2->model = glm::translate(moon2->model, moon2Pos);
	moon3->model = glm::translate(moon3->model, moon3Pos);

	earth->model = glm::translate(earth->model, earthPos);
	earth->model = glm::rotate(earth->model, glm::radians(earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	earth->model = glm::scale(earth->model, glm::vec3(earthSize));

	earthLine->model = glm::translate(earthLine->model, earthPos);
	earthLine->model = glm::rotate(earthLine->model, glm::radians(earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	earthLine->model = glm::scale(earthLine->model, glm::vec3(earthSize));

	moon1->model = glm::translate(moon1->model, earthPos);
	moon1->model = glm::rotate(moon1->model, glm::radians(earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon1->model = glm::scale(moon1->model, glm::vec3(moon1Size));
	
	moon2->model = glm::translate(moon2->model, earthPos);
	moon2->model = glm::rotate(moon2->model, glm::radians(earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon2->model = glm::scale(moon2->model, glm::vec3(moon2Size));

	moon3->model = glm::translate(moon3->model, earthPos);
	moon3->model = glm::rotate(moon3->model, glm::radians(earthRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon3->model = glm::scale(moon3->model, glm::vec3(moon3Size));












	/*
	Translation vom Mars + Linie
	BITTE NICHT VERÄNDERN!
	PS.: außer du bist lebenmüde
	*/

	mars->render(view, projection);
	marsLine->render(view, projection);

	float marsFactor = marsPosX;
	marsPos = glm::vec3(-cos(marsAngle) * marsFactor, 0, -sin(marsAngle) * marsFactor);

	mars->model = glm::scale(mars->model, glm::vec3(1 / marsSize));
	mars->model = glm::rotate(mars->model, glm::radians(-marsRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	mars->model = glm::rotate(mars->model, glm::radians(-marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	mars->model = glm::translate(mars->model, marsPos);

	marsLine->model = glm::scale(marsLine->model, glm::vec3(1 / marsSize));
	marsLine->model = glm::rotate(marsLine->model, glm::radians(-marsRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	marsLine->model = glm::rotate(marsLine->model, glm::radians(-marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	marsLine->model = glm::translate(marsLine->model, marsPos);

	moon4->model = glm::scale(moon4->model, glm::vec3(1 / moon1Size));
	moon4->model = glm::rotate(moon4->model, glm::radians(-marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon4->model = glm::translate(moon4->model, marsPos);
	moon4->model = glm::translate(moon4->model, -moon4Pos);

	moon5->model = glm::scale(moon5->model, glm::vec3(1 / moon2Size));
	moon5->model = glm::rotate(moon5->model, glm::radians(-marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon5->model = glm::translate(moon5->model, marsPos);
	moon5->model = glm::translate(moon5->model, -moon5Pos);

	moon6->model = glm::scale(moon6->model, glm::vec3(1 / moon3Size));
	moon6->model = glm::rotate(moon6->model, glm::radians(-marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon6->model = glm::translate(moon6->model, marsPos);
	moon6->model = glm::translate(moon6->model, -moon6Pos);

	moon7->model = glm::scale(moon7->model, glm::vec3(1 / moon3Size));
	moon7->model = glm::rotate(moon7->model, glm::radians(-marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon7->model = glm::translate(moon7->model, marsPos);
	moon7->model = glm::translate(moon7->model, -moon7Pos);


	marsAngle += marsAngleFactor;
	marsRotationAxisY += marsRotationAxisYFactor;
	marsPos = glm::vec3(cos(marsAngle) * marsFactor, 0, sin(marsAngle) * marsFactor);

	moon4Pos = glm::vec3(moon4Pos[0] * cos(moon4AngleFactor) - moon4Pos[2] * sin(moon4AngleFactor), moon4Pos[1], moon4Pos[2] * cos(moon4AngleFactor) + moon4Pos[0] * sin(moon4AngleFactor));
	moon5Pos = glm::vec3(moon5Pos[0] * cos(moon5AngleFactor) - moon5Pos[2] * sin(moon5AngleFactor), moon5Pos[1], moon5Pos[2] * cos(moon5AngleFactor) + moon5Pos[0] * sin(moon5AngleFactor));
	moon6Pos = glm::vec3(moon6Pos[0] * cos(moon6AngleFactor) - moon6Pos[2] * sin(moon6AngleFactor), moon6Pos[1], moon6Pos[2] * cos(moon6AngleFactor) + moon6Pos[0] * sin(moon6AngleFactor));
	moon7Pos = glm::vec3(moon7Pos[0] * cos(moon7AngleFactor) - moon7Pos[2] * sin(moon7AngleFactor), moon7Pos[1], moon7Pos[2] * cos(moon7AngleFactor) + moon7Pos[0] * sin(moon7AngleFactor));


	moon4->model = glm::translate(moon4->model, moon4Pos);
	moon5->model = glm::translate(moon5->model, moon5Pos);
	moon6->model = glm::translate(moon6->model, moon6Pos);
	moon7->model = glm::translate(moon7->model, moon7Pos);


	mars->model = glm::translate(mars->model, marsPos);
	mars->model = glm::rotate(mars->model, glm::radians(marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	mars->model = glm::rotate(mars->model, glm::radians(marsRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	mars->model = glm::scale(mars->model, glm::vec3(marsSize));
	
	marsLine->model = glm::translate(marsLine->model, marsPos);
	marsLine->model = glm::rotate(marsLine->model, glm::radians(marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	marsLine->model = glm::rotate(marsLine->model, glm::radians(marsRotationAxisZ), glm::vec3(0.0f, 0.0f, 1.0f));
	marsLine->model = glm::scale(marsLine->model, glm::vec3(marsSize));

	moon4->model = glm::translate(moon4->model, marsPos);
	moon4->model = glm::rotate(moon4->model, glm::radians(marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));

	moon4->model = glm::scale(moon4->model, glm::vec3(moon4Size));

	moon5->model = glm::translate(moon5->model, marsPos);
	moon5->model = glm::rotate(moon5->model, glm::radians(marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon5->model = glm::scale(moon5->model, glm::vec3(moon5Size));

	moon6->model = glm::translate(moon6->model, marsPos);
	moon6->model = glm::rotate(moon6->model, glm::radians(marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon6->model = glm::scale(moon6->model, glm::vec3(moon6Size));

	moon7->model = glm::translate(moon7->model, marsPos);
	moon7->model = glm::rotate(moon7->model, glm::radians(marsRotationAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
	moon7->model = glm::scale(moon7->model, glm::vec3(moon7Size));

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

