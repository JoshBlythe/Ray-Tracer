#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"
#include "Light.h"

Sphere::Sphere(glm::vec3 _sphereCentre, float _sphereRadius, int _sphType)
{
	m_objCentre = _sphereCentre;
	m_objRadius = _sphereRadius;
	m_sphReflectiveness = _sphType;
}

glm::vec3 Sphere::closestPoint(Ray _ray, glm::vec3 _querPoint)
{
	// find the point of the ray
	//glm::vec3 _nPoint = (glm::dot(_querPoint - _ray.m_origin, _ray.m_dir)) * _ray.m_dir;

	glm::vec3 _xPoint = _ray.m_origin + 
		(glm::dot(_querPoint - _ray.m_origin, _ray.m_dir)* _ray.m_dir);

	//glm::vec3 _point;
	return _xPoint;

}

checkCollision Sphere::IsCollision(Ray _ray)
{
	//create instance of checkcollison
	checkCollision collisonCheck;
	//set collision to false
	collisonCheck.m_isColliding = false;
	//get closest point
	glm::vec3 m_xPoint = closestPoint(_ray, m_objCentre);

	//get the magnitude distance between closest point and objects centre
	float distantBetween = glm::length(m_objCentre - m_xPoint);

	//check the magnitude distance between closest point and objects centre against sphere radius
	// this tells us if its inside if it is then there is a collison .
	if (distantBetween <= m_objRadius)
	{
		collisonCheck.m_isColliding = true;

		float distantInside = glm::length(m_objCentre - _ray.m_origin -
		(glm::dot(m_objCentre - _ray.m_origin, _ray.m_dir))* _ray.m_dir);

		//get the directions
		float direction = sqrt(pow(m_objRadius, 2) - pow(distantInside, 2));

		//calculate the collison point
		glm::vec3 m_firstCollison = _ray.m_origin +
			((glm::dot(m_objCentre - _ray.m_origin,_ray.m_dir)) - direction)*_ray.m_dir;

		//store collision position into collisioncheck structure.
		collisonCheck.m_collisionPoint = m_firstCollison;

		//could also find the neariest point of the sphere as this will be needed when
		//rendering multiple spheres
		//get the neariest point and use this to render the first sqhere.
		collisonCheck.m_distToInter = glm::length(_ray.m_origin - m_firstCollison);

	}
	//else not inside so iscolliding is false.
	else
	{
		//setting varible to false.
		
	}

	//return the collison point this will be found using caculation from slides.
	return collisonCheck;
}

glm::vec3 Sphere::objNormal(glm::vec3 _pointSmple)
{
	//calulating the surface normal
	glm::vec3 _surfNormal = glm::normalize(m_objCentre - _pointSmple);
	//return the normalised surface normal vector.
	return _surfNormal;
}

glm::vec3 Sphere::shadePixel(Ray _ray, glm::vec3 _iterSec, Light _light)
{
	glm::vec3 _diffLight;
	//normalised surface of sphere
	glm::vec3 _sphNorm = objNormal(_iterSec);	
	//lights directions
	glm::vec3 _lightDir = glm::normalize(_iterSec - _light.m_lightPos);
	
	//return colour declare
	_matCol = { 1, 0, 0 };

	_diffLight = glm::max(0.0f, glm::dot(_lightDir, _sphNorm)) * _light.m_lightCol * _matCol;
	////create ray from intersected point in the direction of the light

	////Ray _testShadows = m_camera.lock()->shadowRay(_intersectionPoint + _sphNorm * 0.001f, -_lightDir);
	////checkCollision _shadowCheck = IsCollision(_testShadows);
	////test if ray is colliding
	//
	////checks if iscollsion is = to true, instead of below.
	////cant do this becasue is of type checkcollison.
	//
	////bool _isVisible = !_shadowCheck.m_isColliding;
	////if ray has collided
	////if (_isVisible)
	//{
	//	//is in shadow
	//	_diffLight += _light.m_lightIntensity * _light.m_lightCol * glm::max(0.0f, glm::dot(_sphNorm, -_lightDir));
	//}


	//return value
	return _diffLight;
}


