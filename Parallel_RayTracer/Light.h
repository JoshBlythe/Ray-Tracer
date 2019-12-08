#pragma once

//#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/glm.hpp>

class Light
{
public:
	glm::vec3 m_lightPos;
	glm::vec3 m_lightCol;
	float m_lightIntensity;

	//glm::vec3 m_lightDir;
};