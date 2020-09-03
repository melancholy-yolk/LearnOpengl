#ifndef MYCAMERA_H
#define MYCAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CameraMoveDir
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;

class MyCamera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;//�������y��������
	glm::vec3 Right;
	glm::vec3 WorldUp;//ʼ����(0, 1, 0)

	float MoveSpeed;
	float MouseSensitivity;
	float Fov;//�������fovֵ

	float Pitch;
	float Yaw;//������ĸ����Ǻ�ƫ����

	MyCamera(glm::vec3 cameraPos)
	{
		Position = cameraPos;

		WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		Yaw = YAW;
		Pitch = PITCH;
		Fov = FOV;

		MoveSpeed = SPEED;
		MouseSensitivity = SENSITIVITY;

		updateCameraVectors();
	}

	//���ݵ�ǰcamera������۲����
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	void processKeyBoard(CameraMoveDir dir, float deltaTime)
	{
		float velocity = MoveSpeed * deltaTime;
		switch (dir)
		{
			case FORWARD:
				Position += Front * velocity;
				break;
			case BACKWARD:
				Position -= Front * velocity;
				break;
			case LEFT:
				Position -= Right * velocity;
				break;
			case RIGHT:
				Position += Right * velocity;
				break;
		}
	}

	void processMouse(float xoffset, float yoffset)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		//���Ƹ�����
		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}
		if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void processScroll(double yoffset)
	{
		if (Fov >= 1.0f && Fov <= 45.0f)
			Fov -= yoffset;
		if (Fov <= 1.0f)
			Fov = 1.0f;
		if (Fov >= 45.0f)
			Fov = 45.0f;
	}
private:
	//calculates the front vector from the camera's Euler Angles
	void updateCameraVectors()
	{
		glm::vec3 front = glm::vec3(1.0f);
		front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
		front.y = sin(glm::radians(Pitch));
		front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
		Front = glm::normalize(front);

		Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}
};

#endif