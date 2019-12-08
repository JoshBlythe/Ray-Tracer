#include <iostream>
#include <cmath>
#include <ctime>
#include <memory>

#include "CGG_Main.h"
#include "Scene.h"

#undef main
#ifdef _MSC_VER
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main(int argc, char *argv[])
{
	//create a pointer to Scene to access the render function.
	std::shared_ptr<Scene>_scene = std::make_shared<Scene>();
	
	//initalise window size
	int m_wWindow = 680;
	int m_hWindow = 480;

	//std::shared_ptr<Ray_Tracer>_rayTracer = std::make_shared<Ray_Tracer>();

	//create window
	if (!CGG::Init (m_wWindow, m_hWindow))
	{
		return -1;
	}

	//time on compiling
	float _compileTime;
	clock_t _time;

	_time = clock();

	for (int i = 0; i < 100000; i++)
	{
		_compileTime = log(pow(i, 5));
	}

	_time = clock() - _time;

	std::cout << "Time Taken: " << (float)_time / CLOCKS_PER_SEC << std::endl;

	_scene->Init(m_wWindow, m_hWindow);

	//call render scene render function
	_scene->Render();

	
	//Display to screen and wait for user input
	return CGG::ShowAndHold();
}