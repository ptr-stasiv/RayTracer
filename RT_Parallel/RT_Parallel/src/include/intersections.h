#pragma once
#ifdef RT_DLL
	#define RT_API __declspec(dllexport)
#else
	#define RT_API __declspec(dllimport)
#endif

#include <cstdint>
#include "rt_math.h"

namespace cuda
{
	struct Sphere
	{
		Vector3 Center;
		float Radius;
	};

	extern "C" void RT_API Render(Sphere* sphere, Vector3 cameraPosition, const uint16_t sizeX, const uint16_t sizeY, Vector3* frameBuffer);
}