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

using namespace std;

//系统事件回调函数
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
bool mouseFirst = true;//是否第一次移动鼠标 

float deltaTime = 0.0f;//当前帧与前一帧间隔
float lastFrame = 0.0f;//上一帧时间


glm::vec3 lightCubePos(1.2f, 1.0f, 2.0f);//作为光源的cube在世界空间中的位置

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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏并捕捉光标

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);//开启深度测试

	//使用我们自己封装的Shader对象 来简化着色器的创建、编译 着色器程序的附加、链接
	Shader objShader("C:/Users/P7XXTM1-G/Desktop/shader/MultipleLight/vert.txt", "C:/Users/P7XXTM1-G/Desktop/shader/MultipleLight/fragSpotLight.txt");
	Shader lightCubeShader("C:/Users/P7XXTM1-G/Desktop/shader/vertLight.txt", "C:/Users/P7XXTM1-G/Desktop/shader/fragLight.txt");
	
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

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

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f, 0.2f, 2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f, 2.0f, -12.0f),
		glm::vec3(0.0f, 0.0f, -3.0f)
	};

	//两个VAO公用一个VBO 因为立方体顶点数据都一样
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//顺序：开启深度测试 创建shader 创建顶点数据 创建纹理
	MyTexture diffuseMap("C:/Users/P7XXTM1-G/Desktop/photo/container2.png");
	MyTexture specularMap("C:/Users/P7XXTM1-G/Desktop/photo/container2_specular.png");

	objShader.use();
	objShader.setInt("material.diffuse", 0);//指定片元着色器中声明的sampler(纹理采样器)对应几号纹理单元
	objShader.setInt("material.specular", 1);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap.textureID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap.textureID);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();//从glfw初始化到此时经过的秒数
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		processInput(window);

		// render 
		//每次渲染之前 清楚颜色缓冲
		//在每次渲染迭代之前清除深度缓冲 否则前一帧的深度信息仍然保存在缓冲中 就像清除颜色缓冲一样
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//------------------------------------ 设置渲染箱子的着色器程序 ------------------------------------
		objShader.use();
		objShader.setVec3("viewPos", myCamera.Position);

		//给光结构体赋值
		//平行光
		objShader.setVec3("dirLight.direction", glm::vec3(-1.0f));//聚光灯方向
		objShader.setVec3("dirLight.ambient", glm::vec3(0.1f));//环境光
		objShader.setVec3("dirLight.diffuse", glm::vec3(0.8f));//漫反射光照
		objShader.setVec3("dirLight.specular", glm::vec3(1.0f));//镜面光

		//点光源
		objShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		objShader.setVec3("pointLights[0].ambient", glm::vec3(0.1f));//环境光
		objShader.setVec3("pointLights[0].diffuse", glm::vec3(0.8f));//漫反射光照
		objShader.setVec3("pointLights[0].specular", glm::vec3(1.0f));//镜面光
		objShader.setFloat("pointLights[0].constant", 1.0f);
		objShader.setFloat("pointLights[0].linear", 0.09f);
		objShader.setFloat("pointLights[0].quadratic", 0.032f);

		objShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		objShader.setVec3("pointLights[1].ambient", glm::vec3(0.1f));//环境光
		objShader.setVec3("pointLights[1].diffuse", glm::vec3(0.8f));//漫反射光照
		objShader.setVec3("pointLights[1].specular", glm::vec3(1.0f));//镜面光
		objShader.setFloat("pointLights[1].constant", 1.0f);
		objShader.setFloat("pointLights[1].linear", 0.09f);
		objShader.setFloat("pointLights[1].quadratic", 0.032f);

		objShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		objShader.setVec3("pointLights[2].ambient", glm::vec3(0.1f));//环境光
		objShader.setVec3("pointLights[2].diffuse", glm::vec3(0.8f));//漫反射光照
		objShader.setVec3("pointLights[2].specular", glm::vec3(1.0f));//镜面光
		objShader.setFloat("pointLights[2].constant", 1.0f);
		objShader.setFloat("pointLights[2].linear", 0.09f);
		objShader.setFloat("pointLights[2].quadratic", 0.032f);

		objShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		objShader.setVec3("pointLights[3].ambient", glm::vec3(0.1f));//环境光
		objShader.setVec3("pointLights[3].diffuse", glm::vec3(0.8f));//漫反射光照
		objShader.setVec3("pointLights[3].specular", glm::vec3(1.0f));//镜面光
		objShader.setFloat("pointLights[3].constant", 1.0f);
		objShader.setFloat("pointLights[3].linear", 0.09f);
		objShader.setFloat("pointLights[3].quadratic", 0.032f);

		//聚光灯
		objShader.setVec3("spotLight.position", myCamera.Position);//聚光灯光源位置
		objShader.setVec3("spotLight.direction", myCamera.Front);//聚光灯方向
		objShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));//聚光灯内圆锥余弦值
		objShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));//聚光灯内圆锥余弦值
		objShader.setVec3("spotLight.ambient", glm::vec3(0.1f));//环境光
		objShader.setVec3("spotLight.diffuse", glm::vec3(0.8f));//漫反射光照
		objShader.setVec3("spotLight.specular", glm::vec3(1.0f));//镜面光
		objShader.setFloat("spotLight.constant", 1.0f);
		objShader.setFloat("spotLight.linear", 0.09f);
		objShader.setFloat("spotLight.quadratic", 0.032f);

		//给材质结构体赋值
		objShader.setFloat("material.shininess", 32.0f);
		
		//每帧设置观察矩阵 每一帧因为我们用户的输入 会导致摄像机位置、角度发生变化 所以每帧都要重新生成LookAt矩阵
		glm::mat4 view = myCamera.GetViewMatrix();//位置 目标 上向量
		objShader.setMatrix4("view", view);

		//每帧设置透视投影矩阵
		glm::mat4 projection = glm::perspective(glm::radians(myCamera.Fov), 800.0f / 600.0f, 0.1f, 100.0f);
		objShader.setMatrix4("projection", projection);

		

		glBindVertexArray(cubeVAO);//绑定顶点数组对象

		glm::mat4 model = glm::mat4(1.0f);
		for (unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			objShader.setMatrix4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//------------------------------------ 箱子绘制完毕 ------------------------------------


		//------------------------------------ 设置渲染四个点光源的着色器程序 ------------------------------------
		//每次使用一个着色器程序 opengl都会使用刚刚激活的着色器程序对象 渲染接下来要渲染的对象
		lightCubeShader.use();
		lightCubeShader.setMatrix4("view", view);
		lightCubeShader.setMatrix4("projection", projection);
		glBindVertexArray(lightCubeVAO);//绑定顶点数组对象
		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			//每帧设置模型矩阵
			model = glm::translate(model, pointLightPositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			model = glm::scale(model, glm::vec3(0.2f));
			lightCubeShader.setMatrix4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//------------------------------------ 四个点光源渲染完毕 ------------------------------------


		//设置光源的变换矩阵
		/*lightCubeShader.use();
		lightCubeShader.setMatrix4("view", view);
		lightCubeShader.setMatrix4("projection", projection);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightCubePos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightCubeShader.setMatrix4("model", model);*/
		
		//glBindVertexArray(lightCubeVAO);//绑定顶点数组对象
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//使用线框模式渲染
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//使用EBO进行绘制
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();//轮询事件
	}
	//回收内存
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteBuffers(1, &VBO);

	glDeleteProgram(objShader.ID);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	//按下ESC键
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//键盘按键移动摄像机
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