#pragma once

#include <GLM/gtc/matrix_transform.hpp>
#include <memory>

class Ray;

class Camera
{
public:
	Camera();
	~Camera();

	Ray spawnNewRay(glm::vec3 __rayOrigin, glm::vec3 _rayDir);

	Ray createRay(glm::ivec2 _pixelCoordinate, int _windowW, int _windowH);

private:

	glm::mat4 m_viewMat;
	glm::mat4 m_projMat;

};