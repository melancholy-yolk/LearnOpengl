#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//这个类封装了VAO VBO EBO的创建和配置过程 使我们可以直接拿到VAO VBO EBO
class VertexData
{
public:
	unsigned int VAO, VBO, EBO;

	VertexData();//float *vertices, unsigned int *indices

	void deleteData();
};

#endif