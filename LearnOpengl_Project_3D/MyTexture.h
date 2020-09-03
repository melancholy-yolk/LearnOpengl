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
	MyTexture(const char *imagePath);
};

#endif