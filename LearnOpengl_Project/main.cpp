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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//使用我们自己封装的Shader对象 来简化着色器的创建、编译 着色器程序的附加、链接
	Shader ourShader("C:\\Users\\P7XXTM1-G\\Desktop\\shader\\vertex.txt", "C:\\Users\\P7XXTM1-G\\Desktop\\shader\\fragment.txt");

	VertexData *vertexData = new VertexData();
	
	MyTexture texture1("C:\\Users\\P7XXTM1-G\\Desktop\\图片\\bg.jpg");
	MyTexture texture2("C:\\Users\\P7XXTM1-G\\Desktop\\图片\\RedWallPaper.jpg");

	ourShader.use();
	//设置着色器代码中的uniform采样器
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//将纹理绑定到对应的纹理单元
		glActiveTexture(GL_TEXTURE0);//激活纹理单元0
		glBindTexture(GL_TEXTURE_2D, texture1.textureID);
		glActiveTexture(GL_TEXTURE1);//激活纹理单元1
		glBindTexture(GL_TEXTURE_2D, texture2.textureID);

		//配置着色器代码中的uniform
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));//uniform位置值 矩阵个数 是否转置 矩阵
		ourShader.setFloat("delta", sin(glfwGetTime())/2.0f + 0.5f);

		glBindVertexArray(vertexData->VAO);//绑定顶点数组对象
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//使用线框模式渲染
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//使用EBO进行绘制

		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		float scale = sin(glfwGetTime());
		trans = glm::scale(trans, glm::vec3(scale, scale, scale));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//使用EBO进行绘制

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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}