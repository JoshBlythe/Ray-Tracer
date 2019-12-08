#include <GLM/gtc/matrix_transform.hpp>

class Ray_Class
{
public:
	Ray_Class();
	~Ray_Class();

protected:

	//ray origin and direction
	glm::fvec3 m_rayOrigin;

	glm::fvec3 m_rayDir;


};