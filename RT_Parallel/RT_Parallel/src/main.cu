#include "cuda.h"
#include "cuda_runtime_api.h"

__global__ void Intersection_GPU()
{

}

__declspec(dllexport) void Intersection()
{
	Intersection_GPU<<<1,1>>>();
}