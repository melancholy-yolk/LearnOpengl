#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <filesystem>

#include "model.h"
#include "shader.h"
#include "MyCamera.h"


using namespace std;

void setShader_DirLight(Shader ourShader);
void setShader_SpotLight(Shader ourShader);

//ϵͳ�¼��ص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

MyCamera myCamera(glm::vec3(0.0f, 0.0f, 3.0f));
float mousePosLastFrameX = SCR_WIDTH / 2.0f;
float mousePosLastFrameY = SCR_HEIGHT / 2.0f;
bool mouseFirst = true;//�Ƿ��һ���ƶ���� 

float deltaTime = 0.0f;//��ǰ֡��ǰһ֡���
float lastFrame = 0.0f;//��һ֡ʱ��


glm::vec3 lightCubePos(1.2f, 1.0f, 2.0f);//��Ϊ��Դ��cube������ռ��е�λ��

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f, 0.2f, 2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f, 2.0f, -12.0f),
	glm::vec3(0.0f, 0.0f, -3.0f)
};

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
	stbi_set_flip_vertically_on_load(true);
	glEnable(GL_DEPTH_TEST);//������Ȳ���

	//ʹ�������Լ���װ��Shader���� ������ɫ���Ĵ��������� ��ɫ������ĸ��ӡ�����
	Shader ourShader("C:/Users/P7XXTM1-G/Desktop/shader/Model/vertModel.txt", "C:/Users/P7XXTM1-G/Desktop/shader/Model/fragModel.txt");
	
	Model ourModel("C:/Users/P7XXTM1-G/Desktop/photo/model/nanosuit.obj");

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
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		ourShader.use();

		setShader_DirLight(ourShader);

		//���Դ
		ourShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		ourShader.setVec3("pointLights[0].ambient", glm::vec3(0.1f));//������
		ourShader.setVec3("pointLights[0].diffuse", glm::vec3(0.8f));//���������
		ourShader.setVec3("pointLights[0].specular", glm::vec3(1.0f));//�����
		ourShader.setFloat("pointLights[0].constant", 1.0f);//����˥������
		ourShader.setFloat("pointLights[0].linear", 0.09f);//˥��һ����
		ourShader.setFloat("pointLights[0].quadratic", 0.032f);//˥��������

		ourShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		ourShader.setVec3("pointLights[1].ambient", glm::vec3(0.1f));//������
		ourShader.setVec3("pointLights[1].diffuse", glm::vec3(0.8f));//���������
		ourShader.setVec3("pointLights[1].specular", glm::vec3(1.0f));//�����
		ourShader.setFloat("pointLights[1].constant", 1.0f);
		ourShader.setFloat("pointLights[1].linear", 0.09f);
		ourShader.setFloat("pointLights[1].quadratic", 0.032f);

		ourShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		ourShader.setVec3("pointLights[2].ambient", glm::vec3(0.1f));//������
		ourShader.setVec3("pointLights[2].diffuse", glm::vec3(0.8f));//���������
		ourShader.setVec3("pointLights[2].specular", glm::vec3(1.0f));//�����
		ourShader.setFloat("pointLights[2].constant", 1.0f);
		ourShader.setFloat("pointLights[2].linear", 0.09f);
		ourShader.setFloat("pointLights[2].quadratic", 0.032f);

		ourShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		ourShader.setVec3("pointLights[3].ambient", glm::vec3(0.1f));//������
		ourShader.setVec3("pointLights[3].diffuse", glm::vec3(0.8f));//���������
		ourShader.setVec3("pointLights[3].specular", glm::vec3(1.0f));//�����
		ourShader.setFloat("pointLights[3].constant", 1.0f);
		ourShader.setFloat("pointLights[3].linear", 0.09f);
		ourShader.setFloat("pointLights[3].quadratic", 0.032f);

		setShader_SpotLight(ourShader);

		//�����ʽṹ�帳ֵ
		ourShader.setFloat("material.shininess", 32.0f);
		ourShader.setVec3("viewPos", myCamera.Position);

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(myCamera.Fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = myCamera.GetViewMatrix();
		ourShader.setMatrix4("projection", projection);
		ourShader.setMatrix4("view", view);

		// render the loaded model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f));	// it's a bit too big for our scene, so scale it down
		ourShader.setMatrix4("model", model);

		ourModel.Draw(ourShader);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();//��ѯ�¼�
	}

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