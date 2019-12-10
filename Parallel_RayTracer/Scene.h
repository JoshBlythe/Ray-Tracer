#pragma once

#include <GLM/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>

class Plane;
class Sphere;
class Camera;
class Tracer;



#include "Light.h"

class Scene
{
public:
	Scene();
	~Scene();

	void Init(int _windowW, int _windowH);

	void WindowSections(int _threadStartX, int _threadendPosX);

	void Render();


private:
	int m_windowW, m_windowH;
	
	std::shared_ptr<Camera> m_cam;
	std::shared_ptr<Tracer> m_tracer;

	std::shared_ptr<Plane> _plane;
	std::vector < std::shared_ptr<Sphere>> m_spheres;

	Light m_light;

	//create mutex for threads
	std::mutex _mute;
	//vector of threads
	std::vector<std::thread> m_nThread;


};

