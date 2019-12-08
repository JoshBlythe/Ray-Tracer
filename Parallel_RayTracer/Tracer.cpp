#include "Tracer.h"
#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
//#include "Light.h"

Tracer::Tracer()
{
}

Tracer::~Tracer()
{
}

glm::vec3 Tracer::traceRay(Ray &_ray, std::vector<std::shared_ptr<Sphere>> &_sphereVec, Light &_light)
{	
	//declare colour
	//m_lightVec.push_back(_light);
	ObjectCheck _objectTest;
	//checkCollision _checkIntersection = _objectTest._closestSphere.lock()->IsCollision(_ray);
	glm::vec3 _rtnCol;
	//float _colPoint = INFINITY;

	if (IntersectionCheck(_ray, _sphereVec, _light, _objectTest))
	{
		//return colour of sphere
		_rtnCol = _objectTest._colour;
	}

	glm::vec3 _collPoint = _ray.m_origin + _ray.m_dir * _objectTest._intersectionDistance;
	glm::vec3 _normal = _objectTest._closestSphere->objNormal(_objectTest._intersectionLoc);
	glm::vec3 _lightDir = glm::normalize(_objectTest._intersectionLoc - _light.m_lightPos);


	switch (_objectTest._closestSphere->getSphereType())
	{
	case(0):
	{
		//if diffuse
		ObjectCheck _shadowCheck;
		Ray _shadowTest = m_cam->spawnNewRay(_collPoint + _normal * 0.001f, -_lightDir);

		bool _isVis = !IntersectionCheck(_shadowTest, _sphereVec, _light, _shadowCheck);

		if (_isVis)
		{
			_rtnCol += _light.m_lightIntensity * _objectTest._closestSphere->getMaterialCol() *
				glm::max(0.0f, glm::dot(_normal, -_lightDir));
		}
		break;
	}

	case(1):
	{
		//has reflection.
		glm::vec3 _reflect = objectReflection(_ray.m_dir, _collPoint);

		Ray _reflectionRay = m_cam->spawnNewRay(_collPoint + _normal * 0.001f, _reflect);

		_rtnCol += 0.8f * traceRay(_reflectionRay, _sphereVec, _light);

		break;
	}

	default:
		_rtnCol = _objectTest._colour;
		break;
	}

	//ObjectCheck _shadeObj;
	

	//for (std::shared_ptr<Sphere> _spheres : _sphereVec)
	//{
	//	_checkIntersection = _spheres->IsCollision(_ray);
	//	if (_checkIntersection.m_isColliding)
	//	{
	//		if (_checkIntersection.m_distToInter < _colPoint)
	//		{
	//			_colPoint = _checkIntersection.m_distToInter;
	//			//_closestSphere = _spheres;
	//			_rtnCol = _spheres->shadePixel(_ray, _checkIntersection.m_collisionPoint,_light);
	//		}
	//	}
	//}
	//for (std::shared_ptr<Sphere> _sphereShadow : _sphereVec)
	//{
	//	glm::vec3 _normal = _sphereShadow->objNormal(_collPoint);
	//	//create the shadow ray.
	//	Ray _shadowTest = m_cam->shadowRay(_collPoint + _normal * 0.001f, -_lightDir);
	//	////test for collision 
	//	checkCollision _shadeObject = _sphereShadow->IsCollision(_shadowTest);
	//	bool _isVis = !_shadeObject.m_isColliding;
	//	if (_shadeObject.m_isColliding)
	//	{
	//		_rtnCol += _light.m_lightIntensity * _sphereShadow->getMaterialCol() * glm::max(0.0f,
	//			glm::dot(_normal, -_lightDir));
	//		//_rtnCol = { 0, 0, 0 };
	//	}
	//}

	return _rtnCol;
}

bool Tracer::IntersectionCheck(Ray _ray, std::vector<std::shared_ptr<Sphere>> _sphereVec, Light _light, ObjectCheck &_object)
{
	float _colPoint = INFINITY;
	
	//for (std::shared_ptr<Sphere> _spheres : _sphereVec)
	//{
	//	checkCollision _checkIntersection = _spheres->IsCollision(_ray);
	//	_object._closestSphere = _spheres;

	//	_object._intersectionDistance = _checkIntersection.m_distToInter;

	//	if (_checkIntersection.m_isColliding)
	//	{
	//		//_object.m_isIntersection = _checkIntersection.m_isColliding;
	//		_object._intersectionLoc = _checkIntersection.m_collisionPoint;

	//		if (_checkIntersection.m_distToInter < _colPoint)
	//		{
	//			_colPoint = _checkIntersection.m_distToInter;
	//			_object._colour = _spheres->shadePixel(_ray, _checkIntersection.m_collisionPoint, _light);
	//			//_check._intersectionLoc = _checkIntersection.m_collisionPoint;
	//			//return true;

	//		}
	//	}

	//}

	for (std::shared_ptr<Sphere> _spheres : _sphereVec)
	{
		checkCollision _checkIntersection = _spheres->IsCollision(_ray);
		_object._closestSphere = _spheres;

		_object._intersectionDistance = _checkIntersection.m_distToInter;
		_object._intersectionLoc = _checkIntersection.m_collisionPoint;
		_object.m_isIntersection = _checkIntersection.m_isColliding;

		if (_object.m_isIntersection)
		{
			//_object.m_isIntersection = _checkIntersection.m_isColliding;
			
			if (_object._intersectionDistance < _colPoint)
			{
				_colPoint = _object._intersectionDistance;
				_object._colour = _spheres->shadePixel(_ray, _checkIntersection.m_collisionPoint, _light);
				//_check._intersectionLoc = _checkIntersection.m_collisionPoint;
				//return true;

			}
		}

	}

	//return true;
	return true;
}

glm::vec3 Tracer::objectReflection(glm::vec3 _i, glm::vec3 _norm)
{
	return _i - 2 * glm::dot(_i, _norm) * _norm;
}



