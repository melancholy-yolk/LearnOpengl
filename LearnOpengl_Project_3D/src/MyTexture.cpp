#include "MyTexture.h"

MyTexture::MyTexture(const char *imagePath)
{
	//��ȡͼƬ
	//�����ע�⵽�������µߵ��ˣ�������ΪOpenGLҪ��y��0.0��������ͼƬ�ĵײ��ģ�����ͼƬ��y��0.0����ͨ���ڶ����������ˣ�stb_image.h�ܹ���ͼ�����ʱ�������Ƿ�תy�ᣬֻ��Ҫ�ڼ����κ�ͼ��ǰ����������伴�ɣ�
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

	//�����������
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//���������������
	//������������Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//�������������˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);//�ͷ�ͼ���ڴ�
}