#ifndef VERTICES_H
#define VERTICES_H

#include <glm/glm.hpp>
#include <vector>

float vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};

float skyboxVertices[] = {
	// positions          
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

float cubeVertices[] = {
	// Back face
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // Bottom-left
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom-right         
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
	// Front face
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top-right
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top-right
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top-left
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
	// Left face
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-right
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-left
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-right
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-right
	// Right face
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-left
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right         
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-left
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left     
	// Bottom face
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // top-left
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-left
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-left
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-right
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
	// Top face
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right     
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f  // bottom-left        
};

float planeVertices[] = {
	// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
	5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
	-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
	-5.0f, -0.5f, 5.0f, 0.0f, 0.0f,


	-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
	5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
	5.0f, -0.5f, -5.0f, 2.0f, 2.0f
};

float transparentVertices[] = {
	// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
	0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
	0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
	1.0f, -0.5f, 0.0f, 1.0f, 1.0f,

	0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
	1.0f, -0.5f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.5f, 0.0f, 1.0f, 0.0f
};

//草的位置
std::vector<glm::vec3> vegetation
{
	glm::vec3(-1.5f, 0.0f, -0.48f),
	glm::vec3(1.5f, 0.0f, 0.51f),
	glm::vec3(0.0f, 0.0f, 0.7f),
	glm::vec3(-0.3f, 0.0f, -2.3f),
	glm::vec3(0.5f, 0.0f, -0.6f)
};

//framebuffer纹理附件的顶点数据
float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// positions   // texCoords
	-1.0f, 1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f,
	1.0f, -1.0f, 1.0f, 0.0f,

	-1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 1.0f
};

#endif 