#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLSLProgram.h"
#include "Object.h"

namespace cg
{
	class Line
	{
	public:
		// Create a wired sphere with the given color.
		Line(const glm::vec3& color = glm::vec3(0.9f))
		{
			Line::initShader(programSimple, "shader/simple.vert", "shader/simple.frag");

			initObject(color);
		}

		void render(const glm::mat4& view, const glm::mat4& projection)
		{
			// Create mvp.
			glm::mat4 mvp = projection * view * model;

			// Bind the shader program and set uniform(s).
			programSimple.use();
			programSimple.setUniform("mvp", mvp);

			// Bind vertex array object so we can render the triangle.
			glBindVertexArray(objSphere.vao);
			glDrawElements(GL_LINES, objSphere.indexCount, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glPopMatrix();
		}
	private:
		void initObject(const glm::vec3& color)
		{
			// Build the sphere. Hardcoded *sigh*
			std::vector<glm::vec3> colors;
			std::vector<glm::vec3> positions = { { 0, -500, 0 },{ 0,500,0 } };
			std::vector<GLuint> indices = { 0,1 };
			colors.push_back(color);

			GLuint programId = programSimple.getHandle();
			GLuint pos;

			// Vertex array object.
			glGenVertexArrays(1, &objSphere.vao);
			glBindVertexArray(objSphere.vao);

			// Position buffer.
			glGenBuffers(1, &objSphere.positionBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, objSphere.positionBuffer);
			glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);

			pos = glGetAttribLocation(programId, "position");
			glEnableVertexAttribArray(pos);
			glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Color buffer.
			glGenBuffers(1, &objSphere.colorBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, objSphere.colorBuffer);
			glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

			pos = glGetAttribLocation(programId, "color");
			glEnableVertexAttribArray(pos);
			glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Index buffer.
			objSphere.indexCount = (GLuint)indices.size();

			glGenBuffers(1, &objSphere.indexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objSphere.indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, objSphere.indexCount * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
		}

		static void initShader(GLSLProgram& program, const std::string& vert, const std::string& frag)
		{
			if (!program.compileShaderFromFile(vert.c_str(), cg::GLSLShader::VERTEX))
			{
				throw std::runtime_error(program.log());
			}

			if (!program.compileShaderFromFile(frag.c_str(), cg::GLSLShader::FRAGMENT))
			{
				throw std::runtime_error(program.log());
			}

			if (!program.link())
			{
				throw std::runtime_error(program.log());
			}
		}
	public:
		// Only public for easy access.
		glm::mat4 model;
	private:
		GLSLProgram programSimple;
		Object objSphere;
	};
} // namespace cg

#endif // SPHERE_H#pragma once
