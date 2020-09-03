#ifndef MYTEXTURE_H
#define MYTEXTURE_H

#include <glad/glad.h>

#include "stb_image.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class MyTexture
{
public:
	unsigned int textureID;
	int width, height, nrChannels;
	MyTexture(const char *imagePath)
	{
		glGenTextures(1, &textureID);
		unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum format;
			if (nrChannels == 1)
			{
				format = GL_RED;
			}
			else if (nrChannels == 3)
			{
				format = GL_RGB;
			}
			else if (nrChannels == 4)
			{
				format = GL_RGBA;
			}
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << imagePath << std::endl;
			stbi_image_free(data);
		}
	}
};

#endif