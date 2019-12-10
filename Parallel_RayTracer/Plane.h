#pragma once

#include <GLM\glm.hpp>

class Plane
{
public:
	Plane(glm::vec3 _pos);

private:
	glm::vec3 m_planePosition;
};
