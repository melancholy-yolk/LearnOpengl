#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "model.h"//�Զ���ģ����
#include "shader.h"//�Զ���shader�� shader����link��ɫ�� ������ɫ���������ı�������������Ӧ������Ԫ ���� �任����ȣ�
#include "MyCamera.h"//�Զ���������� ÿ֡��Ҳ����ı������λ�� ���������λ�ü�����µ�view�۲���� projectionͶӰ����
#include "vertices.h"

//��Ⱦ�������̣�
//����opengl��ȫ��״̬ ���ֲ���
//�õ���ɫ������
//�õ���������VAO VBO EBO��
//�õ�Texture
//������ɫ����������:���ø��ֱ任���� ��������Ӧ������Ԫ ��������Ԫ ������


using namespace std;

void setShader_DirLight(Shader ourShader);
void setShader_SpotLight(Shader ourShader);

//ϵͳ�¼��ص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(char const *path);
unsigned int loadCubemap(vector<std::string> faces);
void configureFramebuffer(unsigned int *fb, unsigned int* texture, unsigned int *renderBufferObject);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

MyCamera myCamera(glm::vec3(0.0f, 0.0f, 3.0f));
float mousePosLastFrameX = SCR_WIDTH / 2.0f;
float mousePosLastFrameY = SCR_HEIGHT / 2.0f;
bool mouseFirst = true;//�Ƿ��һ���ƶ���� 

float deltaTime = 0.0f;//��ǰ֡��ǰһ֡���
float lastFrame = 0.0f;//��һ֡ʱ��

int main()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//���ز���׽���

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//stbi_set_flip_vertically_on_load(true);
	
	//����ȫ�ֵ�opengl״̬
	glEnable(GL_DEPTH_TEST);

	//ʹ�������Լ���װ��Shader���� ������ɫ���Ĵ��������� ��ɫ������ĸ��ӡ�����
	Shader objShader("C:/Users/P7XXTM1-G/Desktop/shader/skybox/vertObj.txt", 
					 "C:/Users/P7XXTM1-G/Desktop/shader/skybox/fragObj.txt");

	Shader reflectShader("C:/Users/P7XXTM1-G/Desktop/shader/skybox/vertReflectAndRefract.txt",
						 "C:/Users/P7XXTM1-G/Desktop/shader/skybox/fragReflect.txt");

	Shader refractShader("C:/Users/P7XXTM1-G/Desktop/shader/skybox/vertReflectAndRefract.txt",
						 "C:/Users/P7XXTM1-G/Desktop/shader/skybox/fragRefract.txt");

	Shader ourShader("C:/Users/P7XXTM1-G/Desktop/shader/Model/vertModel.txt",
						"C:/Users/P7XXTM1-G/Desktop/shader/Model/fragModel.txt");

	Shader skyboxShader("C:/Users/P7XXTM1-G/Desktop/shader/skybox/vertSkybox.txt", 
					    "C:/Users/P7XXTM1-G/Desktop/shader/skybox/fragSkybox.txt");
	
	Model myModel("C:/Users/P7XXTM1-G/Desktop/photo/nanosuit_reflection/nanosuit.obj");

	//�ҵ���⣺
	//glGenxxxx�����������Ƿ����һ���ڴ���Ϊ��ʱ����
	//GL_ARRAY_BUFFER��ϵͳ�Ĺ̶��Ļ���Ŀ�� ���ǽ��Լ������Ļ�����ϵͳ�Ļ���Ŀ��� 
	//����ʹ��glBufferData�������ڴ��������

	//skybox VAO
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// cube VAO
	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

	/*unsigned int reflectVAO, reflectVBO;
	glGenVertexArrays(1, &reflectVAO);
	glGenBuffers(1, &reflectVBO);
	glBindVertexArray(reflectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, reflectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);*/

	unsigned int cubeTexture = loadTexture("C:/Users/P7XXTM1-G/Desktop/photo/container2.png");

	vector<string> faces
	{
		"C:/Users/P7XXTM1-G/Desktop/photo/skybox/right.jpg",
		"C:/Users/P7XXTM1-G/Desktop/photo/skybox/left.jpg",
		"C:/Users/P7XXTM1-G/Desktop/photo/skybox/top.jpg",
		"C:/Users/P7XXTM1-G/Desktop/photo/skybox/bottom.jpg",
		"C:/Users/P7XXTM1-G/Desktop/photo/skybox/front.jpg",
		"C:/Users/P7XXTM1-G/Desktop/photo/skybox/back.jpg"
	};
	unsigned int cubemapTexture = loadCubemap(faces);

	objShader.use();
	objShader.setInt("texture1", 0);

	reflectShader.use();
	reflectShader.setInt("skybox", 0);//��ƬԪ��ɫ���������Ĳ�����ָ����Ӧ������Ԫ

	refractShader.use();
	refractShader.setInt("skybox", 0);

	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	ourShader.use();
	ourShader.setInt("material.skybox", 3);

	// draw as wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();//��glfw��ʼ������ʱ����������
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		processInput(window);

		// render 
		//ÿ����Ⱦ֮ǰ �����ɫ����
		//��ÿ����Ⱦ����֮ǰ�����Ȼ��� ����ǰһ֡�������Ϣ��Ȼ�����ڻ����� ���������ɫ����һ��
		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw objects
		objShader.use();
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = myCamera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(myCamera.Fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		
		objShader.setMatrix4("view", view);
		objShader.setMatrix4("projection", projection);
		// cubes
		glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		model = glm::mat4(1.0f);
		objShader.setMatrix4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(cubeVAO);

		//ģ�� ����
		reflectShader.use();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.0f, 0, 0));
		model = glm::scale(model, glm::vec3(0.1f));
		reflectShader.setMatrix4("model", model);
		reflectShader.setMatrix4("view", view);
		reflectShader.setMatrix4("projection", projection);
		reflectShader.setVec3("cameraPos", myCamera.Position);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		myModel.Draw(reflectShader);

		//ģ�� ����
		refractShader.use();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0, 0));
		model = glm::scale(model, glm::vec3(0.1f));
		refractShader.setMatrix4("model", model);
		refractShader.setMatrix4("view", view);
		refractShader.setMatrix4("projection", projection);
		refractShader.setVec3("cameraPos", myCamera.Position);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		myModel.Draw(refractShader);

		//ģ�ͱ�Ե��
		ourShader.use();

		setShader_DirLight(ourShader);//ƽ�й�
		setShader_SpotLight(ourShader);//�۹��

		//�����ʽṹ�帳ֵ
		ourShader.setFloat("material.shininess", 32.0f);
		ourShader.setVec3("viewPos", myCamera.Position);

		ourShader.setMatrix4("projection", projection);
		ourShader.setMatrix4("view", view);model = glm::mat4(1.0f);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3.0f, 0, 0));
		model = glm::scale(model, glm::vec3(0.1f));
		ourShader.setMatrix4("model", model);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

		myModel.Draw(ourShader);

		//��պ�
		glDepthFunc(GL_LEQUAL);
		skyboxShader.use();
		view = glm::mat4(glm::mat3(myCamera.GetViewMatrix())); // remove translation from the view matrix
		skyboxShader.setMatrix4("view", view);
		skyboxShader.setMatrix4("projection", projection);
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();//��ѯ�¼�
	}

	glDeleteProgram(objShader.ID);
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &cubeVBO);

	glDeleteProgram(skyboxShader.ID);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	//����ESC��
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//���̰����ƶ������
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		myCamera.processKeyBoard(CameraMoveDir::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		myCamera.processKeyBoard(CameraMoveDir::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		myCamera.processKeyBoard(CameraMoveDir::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		myCamera.processKeyBoard(CameraMoveDir::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		myCamera.processKeyBoard(CameraMoveDir::UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		myCamera.processKeyBoard(CameraMoveDir::DOWN, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (mouseFirst)
	{
		std::cout << xpos << std::endl;
		std::cout << ypos << std::endl;
		mousePosLastFrameX = xpos;
		mousePosLastFrameY = ypos;
		mouseFirst = false;
	}

	float xoffset = xpos - mousePosLastFrameX;
	float yoffset = mousePosLastFrameY - ypos;// reversed since y-coordinates go from bottom to top

	mousePosLastFrameX = xpos;
	mousePosLastFrameY = ypos;

	myCamera.processMouse(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	myCamera.processScroll(yoffset);
}

unsigned int loadTexture(char const *path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void configureFramebuffer(unsigned int *fb, unsigned int* texture, unsigned int *renderBufferObject)
{
	// framebuffer configuration
	// -------------------------
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// create a color attachment texture
	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it

	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	*fb = framebuffer;
	*texture = textureColorbuffer;
	*renderBufferObject = rbo;
}

unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void setShader_DirLight(Shader ourShader)
{
	//ƽ�й�
	ourShader.setVec3("dirLight.direction", glm::vec3(-1.0f));//ƽ�йⷽ��
	ourShader.setVec3("dirLight.ambient", glm::vec3(1.0f));//������
	ourShader.setVec3("dirLight.diffuse", glm::vec3(1.0f));//���������
	ourShader.setVec3("dirLight.specular", glm::vec3(1.0f));//�����
}

void setShader_PointLight()
{

}

void setShader_SpotLight(Shader ourShader)
{
	//�۹��
	ourShader.setVec3("spotLight.position", myCamera.Position);//�۹�ƹ�Դλ��
	ourShader.setVec3("spotLight.direction", myCamera.Front);//�۹�����䷽��
	ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));//�۹�� ��Բ׶����ֵ
	ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));//�۹�� ��Բ׶����ֵ

	ourShader.setVec3("spotLight.ambient", glm::vec3(0.1f));//������
	ourShader.setVec3("spotLight.diffuse", glm::vec3(0.8f));//���������
	ourShader.setVec3("spotLight.specular", glm::vec3(1.0f));//�����

	ourShader.setFloat("spotLight.constant", 1.0f);
	ourShader.setFloat("spotLight.linear", 0.09f);
	ourShader.setFloat("spotLight.quadratic", 0.032f);
}