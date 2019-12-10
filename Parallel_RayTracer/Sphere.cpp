#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"
#include "Light.h"

Sphere::Sphere(glm::vec3 _sphereCentre, float _sphereRadius, glm::vec3 _sphColour, int _sphType)
{
	m_objCentre = _sphereCentre;
	m_objRadius = _sphereRadius;
	_matCol = _sphColour;
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

		float distantInside = glm::length(m_xPoint - m_objCentre);// glm::length(m_objCentre - _ray.m_origin - (glm::dot(m_objCentre - _ray.m_origin, _ray.m_dir))* _ray.m_dir);

																  //get the directions
		float direction = sqrt(pow(m_objRadius, 2) - pow(distantInside, 2));

		// Distance from ray's origin to intersection point
		float dist = (glm::dot(m_objCentre - _ray.m_origin, _ray.m_dir)) - direction;
		
		// we have an intersection in front of the camera
		if (dist > 0) 
		{
			//set is colliding is true;
			collisonCheck.m_isColliding = true;

			//calculate the collison point
			glm::vec3 m_firstCollison = _ray.m_origin +
				((glm::dot(m_objCentre - _ray.m_origin, _ray.m_dir)) - direction)*_ray.m_dir;

			//store collision position into collisioncheck structure.
			collisonCheck.m_collisionPoint = m_firstCollison;

			//could also find the neariest point of the sphere as this will be needed when
			//rendering multiple spheres
			//get the neariest point and use this to render the first sqhere.
			collisonCheck.m_distToInter = dist;// glm::length(_ray.m_origin - m_firstCollison);


		}

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
	glm::vec3 _surfNormal = glm::normalize(_pointSmple - m_objCentre);
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
	//_matCol = { 1, 0, 0 };

	//diffuse lighting equations.
	_diffLight = glm::max(0.0f, glm::dot(-_lightDir, _sphNorm)) * _light.m_lightCol * _matCol;

	//return value
	return _diffLight;
}


