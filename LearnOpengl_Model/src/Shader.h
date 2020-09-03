#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

typedef struct Material
{
	int diffuse;//ƬԪ��ɫ����sampler2D��Ӧ������Ԫ���
	glm::vec3 specular;
	float shininess;
}Material;

typedef struct Light
{
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
}Light;

class Shader
{
public:
	unsigned int ID;//����ID

	Shader(const char *vertexPath, const char *fragmentPath);//��������ȡ��ɫ�������ӹ�����ɫ������
	void use();//������ɫ������

	//uniform���ߺ��� ����ɫ������������uniform������ֵ
	void setBool(const std::string &name, bool value) const;//����������ɫconstָ���˺��������޸ĳ�Ա������ֵ���������ʱ����
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setFloat4(const std::string &name, float x, float y, float z, float w) const;
	void setMatrix4(const std::string &name, glm::mat4 &matrix4) const;
	void setVec3(const std::string &name, glm::vec3 &vector3) const;

	void setMVP(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection);
	void setModel(glm::mat4 &model);
	void setView(glm::mat4 &view);
	void setProjection(glm::mat4 &projection);

	void setViewPos(glm::vec3 &viewPos);

	void setMaterial(Material &material);
	void setLight(Light &light);
};

#endif
