// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>


class Loader {
public:

	struct HE_edge;

	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec4 > temp_face;
	std::vector< HE_edge > edges;
	std::vector<GLuint> indices;

	struct HE_vert {
		float x;
		float y;
		float z;
		HE_edge* edge; // one of the half-edges emanating from the vertex
	};
	struct HE_face {
		HE_edge* edge; // one of the half-edges bordering the face
	};

	struct HE_edge {
		HE_vert* vert; // start-vertex of the half-edge
		HE_edge* pair; // oppositely oriented adjacent half-edge
		HE_face* face; // face the half-edge borders
		HE_edge* next; // next half-edge around the face
	};

	Loader(char* const path) {
		loadObj(path);
	}

	int loadObj(char* const path)
	{
		FILE * file = fopen(path, "r");
		if (file == NULL) {
			printf("Impossible to open the file !\n");
			return false;
		}
		while (1) {

			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.
			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", vertex[0], &vertex[1], &vertex[2]);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				float vertexf1, vertexf2, vertexf3, vertexf4;
				int matches = fscanf(file, "%f %f %f %f\n", vertexf1, vertexf2, vertexf3, vertexf4);
				if (matches != 3) {
					vertexf4 = -1;
				}
				temp_face.push_back(glm::vec4(vertexf1, vertexf2, vertexf3, vertexf4));
			}
			fclose(file);
			for (int i = 0; i <= temp_face.size(); i++) {
				HE_face face;
				float vert1 = temp_face[i][0];
				float vert2 = temp_face[i][1];
				float vert3 = temp_face[i][2];
				float vert4 = temp_face[i][3];

				HE_vert vertex1;
				vertex1.x = temp_vertices[vert1 - 1][0];
				vertex1.y = temp_vertices[vert1 - 1][1];
				vertex1.z = temp_vertices[vert1 - 1][2];
				HE_edge edge1;
				face.edge = &edge1;
				edge1.vert = &vertex1;
				edge1.face = &face;
				edges.push_back(edge1);

				HE_vert vertex2;
				vertex2.x = temp_vertices[vert2 - 1][0];
				vertex2.y = temp_vertices[vert2 - 1][1];
				vertex2.z = temp_vertices[vert2 - 1][2];
				HE_edge edge2;
				edge2.vert = &vertex2;
				edge2.face = &face;
				edge1.next = &edge2;
				edges.push_back(edge2);

				HE_vert vertex3;
				vertex3.x = temp_vertices[vert3 - 1][0];
				vertex3.y = temp_vertices[vert3 - 1][1];
				vertex3.z = temp_vertices[vert3 - 1][2];
				HE_edge edge3;
				edge3.vert = &vertex3;
				edge3.face = &face;
				edge2.next = &edge3;
				edges.push_back(edge3);

				if (vert4 != -1) {
					HE_vert vertex4;
					vertex4.x = temp_vertices[vert3 - 1][0];
					vertex4.y = temp_vertices[vert3 - 1][1];
					vertex4.z = temp_vertices[vert3 - 1][2];
					HE_edge edge4;
					edge4.vert = &vertex4;
					edge4.face = &face;
					edge3.next = &edge4;
					edge4.next = &edge1;
					edges.push_back(edge4);
				}
				else {
					edge3.next = &edge1;
				}
			}
		}
		float vertex1, vertex2;
		for (int i = 0; i < temp_face.size(); i++) {
			for (int j = 0; i < 3; i++) {
				vertex1 = temp_face[i][j];
				vertex2 = temp_face[i][j + 1];
				for (int m = i; m < temp_face.size(); m++) {
					for (int n = 0; n < 3; n++) {
						if (vertex1 == temp_face[m][n + 1] && vertex2 == temp_face[m][n]) {
							for (int a = 0; a < edges.size(); a++) {
								if (edges[a].vert->x == temp_vertices[vertex2 - 1][0] && edges[a].vert->y == temp_vertices[vertex2 - 1][1] && edges[a].vert->z == temp_vertices[vertex2 - 1][2]) {
									edges[a].pair = &edges[a + 1];
									edges[a + 1].pair = &edges[a];
								}
							}
						}
					}
				}
			}
		}
		for (int i = 0; i < temp_face.size(); i++) {
			for (int j = 0; i < 4; i++) {
				indices.push_back((GLuint)(temp_face[i][j]));
			}
		}

		return 0;
	}

	std::vector<glm::vec3> getVertices() {
		return temp_vertices;
	}
	std::vector<GLuint> getIndices() {
		return indices;
	}
};
