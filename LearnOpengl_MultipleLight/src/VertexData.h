#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//������װ��VAO VBO EBO�Ĵ��������ù��� ʹ���ǿ���ֱ���õ�VAO VBO EBO
class VertexData
{
public:
	unsigned int VAO, VBO, EBO;

	VertexData();//float *vertices, unsigned int *indices

	void deleteData();
};

#endif