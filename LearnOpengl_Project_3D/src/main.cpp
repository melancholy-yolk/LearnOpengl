#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"
#include "MyTexture.h"
#include "VertexData.h"
#include "MyCamera.h"

//ϵͳ�¼��ص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

MyCamera myCamera(glm::vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;//��ǰ֡��ǰһ֡���
float lastFrame = 0.0f;//��һ֡ʱ��

float mousePosLastFrameX = 400, mousePosLastFrameY = 300;
bool mouseFirst = true;//�Ƿ��һ���ƶ���� 

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

	glEnable(GL_DEPTH_TEST);//������Ȳ���

	//ʹ�������Լ���װ��Shader���� ������ɫ���Ĵ��������� ��ɫ������ĸ��ӡ�����
	Shader ourShader("C:/Users/P7XXTM1-G/Desktop/shader/vertex2.txt", "C:/Users/P7XXTM1-G/Desktop/shader/fragment2.txt");

	VertexData *vertexData = new VertexData();

	MyTexture texture1("C:/Users/P7XXTM1-G/Desktop/photo/xiangzi.jpg");
	MyTexture texture2("C:/Users/P7XXTM1-G/Desktop/photo/huaji.jpg");

	ourShader.use();
	//������ɫ�������е�uniform������
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

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
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//������󶨵���Ӧ������Ԫ
		glActiveTexture(GL_TEXTURE0);//��������Ԫ0
		glBindTexture(GL_TEXTURE_2D, texture1.textureID);//������������󶨵��ղż��������Ԫ��
		glActiveTexture(GL_TEXTURE1);//��������Ԫ1
		glBindTexture(GL_TEXTURE_2D, texture2.textureID);

		ourShader.use();
		//ÿ֡���ù۲����
		glm::mat4 view = glm::mat4(1.0f);
		view = myCamera.GetViewMatrix();//λ�� Ŀ�� ������
		ourShader.setMatrix4("view", &view[0][0]);

		//ÿ֡����͸��ͶӰ����
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(myCamera.Fov), 800.0f / 600.0f, 0.1f, 100.0f);
		ourShader.setMatrix4("projection", &projection[0][0]);

		ourShader.setFloat("delta", 0.3);//���������������ɫ�Ĺ���ֵռ��

		glBindVertexArray(vertexData->VAO);//�󶨶����������
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMatrix4("model", &model[0][0]);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//ʹ���߿�ģʽ��Ⱦ
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//ʹ��EBO���л���
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vertexData->deleteData();
	glDeleteProgram(ourShader.ID);

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