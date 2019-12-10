#pragma once

#include <iostream>
#include <GLM/glm.hpp>
#include <memory>
#include <vector>
#include <algorithm>

class Ray;
class Camera;
class Sphere;

//#include "Ray.h"
#include "Light.h"
//#include "Sphere.h"

struct ObjectCheck
{
	std::shared_ptr<Sphere> _closestSphere;
	bool m_isIntersection;
	float _intersectionDistance;
	glm::vec3 _colour;
	glm::vec3 _intersectionLoc;
	//glm::vec3 _ObjectNormal;
};

class Tracer
{
public:
	Tracer();
	~Tracer();
	
	glm::vec3 traceRay(Ray _ray, std::vector<std::shared_ptr<Sphere>> _sphereVec, Light _light, int _depthCheck);
	
	bool IntersectionCheck(Ray _ray, std::vector<std::shared_ptr<Sphere>> _sphereVec, Light _light, ObjectCheck &_object);

	glm::vec3 objectReflection(glm::vec3 &_i, glm::vec3 &_norm);

private:

	//std::shared_ptr<Sphere> _current;

	std::shared_ptr<Camera> m_cam;

	//std::vector<std::shared_ptr<Light>> m_lightVec;
};
