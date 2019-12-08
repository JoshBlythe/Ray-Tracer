#pragma once

#include <GLM/glm.hpp>
#include <memory>
//#include <algorithm>

class Ray;
class Camera;
class Light;


struct checkCollision
{
	bool m_isColliding;
	glm::vec3 m_collisionPoint;
	float m_distToInter;
	//std::weak_ptr<Sphere> _currentSphere;
};

class Sphere
{
public:
	//Sphere() {};
	Sphere(glm::vec3 _sphereCentre, float _sphereRadius, int _sphType);
	//~Sphere();

	//void geoIntersection();

	//static glm::vec3 IsCollision();

	//get the closest point
	glm::vec3 closestPoint(Ray _ray, glm::vec3 _querPoint);
	//ray-intersection with object
	checkCollision IsCollision(Ray _ray);
	//bool checkShadow(Ray _ray, Light _light, std::shared_ptr<Sphere> _object);
	//object normal
	glm::vec3 objNormal(glm::vec3 _pointSmple);
	
	glm::vec3 shadePixel(Ray _ray, glm::vec3 _iterSec, Light _light);
	
	glm::vec3 getMaterialCol() { return _matCol; }
	int getSphereType() { return m_sphReflectiveness; }
	//float GetSphereRadius() { return m_objRadius; }

protected:
	
	std::weak_ptr<Camera> m_camera;

	glm::vec3 _matCol;
	glm::vec3 m_objCentre;
	float m_objRadius;
	int m_sphReflectiveness;

	//glm::vec3 _nPoint;

};
