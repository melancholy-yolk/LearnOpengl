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
	unsigned int ID;//程序ID

	Shader(const char *vertexPath, const char *fragmentPath);//构造器读取着色器并链接构建着色器程序
	void use();//激活着色器程序

	//uniform工具函数
	void setBool(const std::string &name, bool value) const;//函数声明后色const指明此函数不可修改成员变量的值，否则编译时报错
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setFloat4(const std::string &name, float x, float y, float z, float w) const;
};

#endif
