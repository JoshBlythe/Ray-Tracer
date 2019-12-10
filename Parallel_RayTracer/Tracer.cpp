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

glm::vec3 Tracer::traceRay(Ray _ray, std::vector<std::shared_ptr<Sphere>> _sphereVec, Light _light, int _depthCheck)
{	
	//declare colour
	//m_lightVec.push_back(_light);
	ObjectCheck _objectTest;
	//checkCollision _checkIntersection = _objectTest._closestSphere.lock()->IsCollision(_ray);
	glm::vec3 _rtnCol;
	//float _colPoint = INFINITY;

	if (IntersectionCheck(_ray, _sphereVec, _light, _objectTest))
	{
		//check if there is intersection
		if (_objectTest.m_isIntersection)
		{
			//if intersected shade sphere
			_rtnCol = _objectTest._closestSphere->shadePixel(_ray, _objectTest._intersectionLoc, _light);

			//get the intersection location
			glm::vec3 _hit = _objectTest._intersectionLoc;
			//get the sphere surface normal
			glm::vec3 _normal = _objectTest._closestSphere->objNormal(_objectTest._intersectionLoc);
			//get the lights directions
			glm::vec3 _lightDir = glm::normalize(_hit - _light.m_lightPos);

			//get the spheres reflective properties
			switch (_objectTest._closestSphere->getSphereType())
			{
				//if 0 then not reflective
			case(0):
			{
				//test for shadow
				//spawn a new ray from the intersection point back to the light
				Ray _shadowTest = m_cam->spawnNewRay(_hit + _normal * 0.001f, -_lightDir);

				//_rtnCol = _normal;
				ObjectCheck _shadowCheck;

				//if there is a intersection with shadow ray
				if (IntersectionCheck(_shadowTest, _sphereVec, _light, _shadowCheck))
				{
					//if there is a intersection
					if (_shadowCheck.m_isIntersection)
					{
						//return colour is in shadow
						_rtnCol = { 0,0,0 };
					}
				}

				break;
			}
			//if 1 then sphere is reflective.
			case(1):
			{
				/*_rtnCol.g = _rtnCol.r;
				_rtnCol.r = 0.0f;*/
				//check for depth, this stops reflection being recursive
				if (_depthCheck < 3)
				{
					//glm::vec3 _hitNorm = _hit + _normal * 0.001f;
					glm::vec3 _bias = 0.001f * _normal;
					glm::vec3 _reflection = objectReflection(_ray.m_dir, _normal);

					Ray _reflectionRay = m_cam->spawnNewRay(_hit + _normal * _bias, _reflection);

					_rtnCol += 0.8f * traceRay(_reflectionRay, _sphereVec, _light, _depthCheck + 1);
				}

				break;
			}
				
			default:
				break;
			}
		}
	}
	//return ray colour from sphere
	return glm::clamp(_rtnCol,glm::vec3(0),glm::vec3(1));
}

bool Tracer::IntersectionCheck(Ray _ray, std::vector<std::shared_ptr<Sphere>> _sphereVec, Light _light, ObjectCheck &_object)
{
	float _colPoint = INFINITY;

	_object._closestSphere = nullptr;

	for (std::shared_ptr<Sphere> _spheres : _sphereVec)
	{
		checkCollision _checkIntersection = _spheres->IsCollision(_ray);

		if (_checkIntersection.m_isColliding)
		{
			//_object.m_isIntersection = _checkIntersection.m_isColliding;

			if (_checkIntersection.m_distToInter < _colPoint)
			{
				_object._closestSphere = _spheres;
				_colPoint = _checkIntersection.m_distToInter;

				_object._intersectionDistance = _checkIntersection.m_distToInter;
				_object._intersectionLoc = _checkIntersection.m_collisionPoint;
				_object.m_isIntersection = _checkIntersection.m_isColliding;

			}
		}

	}

	//return true;
	return _object._closestSphere != nullptr;
}

glm::vec3 Tracer::objectReflection(glm::vec3 &_i, glm::vec3 &_norm)
{
	return _i - 2 * glm::dot(_i, _norm) * _norm;
}



