#include "Camera.h"
#include "Ray.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

Ray Camera::spawnNewRay(glm::vec3 __rayOrigin, glm::vec3 _rayDir)
{
	Ray _ray;

	_ray.m_origin = __rayOrigin;
	_ray.m_dir = _rayDir;

	return _ray;
}

//Ray Camera::returnRay(glm::ivec2 _pixelCoordinate)
//{
//	// create instance of a ray
//	Ray _ray;
//	
//	// set rays origin and direction.
//	_ray.m_origin = (glm::vec3(_pixelCoordinate,0));
//	_ray.m_dir = (glm::vec3(0,0,-1));
//
//	//return ray
//	return _ray;
//}

Ray Camera::createRay(glm::ivec2 _pixelCoordinate, int _windowW, int _windowH)
{
	Ray _ray;

	m_viewMat = glm::mat4(1);

	//get the read in pixel coordinate to lay between -1 and 1
	float _xPlane = ((float)_pixelCoordinate.x / (float)_windowW) * 2.0f - 1.0f;
	float _yPlane = ((float)_pixelCoordinate.y / (float)_windowH) * 2.0f - 1.0f;

	//store vector for both near and far planes
	glm::vec4 m_nearView = { _xPlane, _yPlane, -1, 1 };
	glm::vec4 m_farView = { _xPlane, _yPlane, 1, 1 };

	//create matrix
	m_projMat = glm::perspective(0.7f, (float)_windowW / (float)_windowH, 0.1f, 100.0f);

	//multiple by inverse matrix
	m_nearView = glm::inverse(m_projMat) * m_nearView;
	m_farView = glm::inverse(m_projMat) * m_farView;

	//divide vector by w value
	m_nearView /= m_nearView.w;
	m_farView /= m_farView.w;


	// set rays origin and direction.
	_ray.m_origin = m_nearView;
	_ray.m_dir = glm::normalize(m_farView - m_nearView);
	
	return _ray;
}




