#include "CGG_Main.h"
#include "Scene.h"
#include "Ray.h"
#include "Camera.h"
#include "Tracer.h"
#include "Sphere.h"

Scene::Scene()
{
	//create initances of both camera and tracers classes
	//gives access to the functions within them.
	m_cam = std::make_shared<Camera>();
	m_tracer = std::make_shared<Tracer>();
}

Scene::~Scene()
{
}

void Scene::Init(int _windowW, int _windowH)
{
	//set read in values to equal member values of the class allowing them to be used
	//by other functions
	m_windowW = _windowW;
	m_windowH = _windowH;

	//creating of spheres.
	std::shared_ptr<Sphere> _s1 = std::make_shared<Sphere>(glm::vec3(1.0f, 0.0f, -8.0f), 1.0f, 1);
	m_spheres.push_back(_s1);
	std::shared_ptr<Sphere> _s2 = std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -10.0f), 2.0f, 0);
	m_spheres.push_back(_s2);
	std::shared_ptr<Sphere> _s3 = std::make_shared<Sphere>(glm::vec3(-2.0f, 0.0f, -12.0f), 1.0f, 0);
	m_spheres.push_back(_s3);

	//initalise light within the screen
	m_light.m_lightPos = { 0.0f, 1.0f, 0.0f };
	m_light.m_lightCol = { 1.0f, 1.0f, 1.0f };
	m_light.m_lightIntensity = 5.0f;

}

void Scene::WindowSections(int _threadStartX, int _threadendPosX)
{ 
	//looping through min and max points of the thread
	for (int x = _threadStartX; x < _threadendPosX; x++)
	{
		//iterate though the height of the screen
		for (int y = 0; y < m_windowH; y++)
		{
			//create variables to store both the pixel points
			glm::ivec2 _pixelPoint = { x, y };
			//and the return colour
			glm::vec3 _rtnColour;

			//create a ray, and call the cameras create ray function
			//send through the pixel points and the window dimentions
			Ray _currentRay = m_cam->createRay(_pixelPoint, m_windowW, m_windowH);
			//the return colour is equal to the return value of the tracers trace function
			_rtnColour = m_tracer->traceRay(_currentRay, m_spheres, m_light);

			//as the values are returned between 0-1 as they come from a shader
			//multiple by 255 to get correct colour values
			_rtnColour *= 255;
			//m_rtnCol = _rtnColour;
			
			//lock the draw function as the values will be access by the created threads
			//stops the values being overriden by each other
			_mute.lock();
			//call the draw pixel function to draw the returned colour at the pixels points
				CGG::DrawPixel(_pixelPoint.x, _pixelPoint.y, _rtnColour.x, _rtnColour.y, _rtnColour.z);
				//unlock the mutex as the function has no longer being used,
				//allows next thread to use.
			_mute.unlock();
		}
	}
}

void Scene::Render()
{
	//create the threads
	for (int x = 0; x < m_windowW; x+=170)
	{
			m_nThread.push_back(std::thread(&Scene::WindowSections, this, x, x + 170));
	}

	// have the threads join / run with in the program.
	for (size_t i = 0; i < m_nThread.size(); i++)
	{
		//check is the thread is able to join/
		if (m_nThread[i].joinable())
		{
			//join the threads
			m_nThread[i].join();
		}

	}
}
