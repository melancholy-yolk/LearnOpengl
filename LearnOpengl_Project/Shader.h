#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID;//����ID

	Shader(const char *vertexPath, const char *fragmentPath);//��������ȡ��ɫ�������ӹ�����ɫ������
	void use();//������ɫ������

	//uniform���ߺ���
	void setBool(const std::string &name, bool value) const;//����������ɫconstָ���˺��������޸ĳ�Ա������ֵ���������ʱ����
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setFloat4(const std::string &name, float x, float y, float z, float w) const;
};

#endif
