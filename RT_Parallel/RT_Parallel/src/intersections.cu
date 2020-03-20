#define RT_DLL
#include <fstream>

#include "cuda.h"
#include "cuda_runtime_api.h"

#include "include/intersections.h"

namespace cuda
{
	__device__ bool Intersection(Sphere* sphere, const Ray& ray, float* t)
	{
		float to = Dot(sphere->Center - ray.Origin, ray.Direction);	//Find the length to the sphere
		Vector3 point = PointAt(ray, to);							//Find intersection point
		float y = Length(sphere->Center - point);					//Find the length from intersect point to sphere center

		if (y > sphere->Radius)
			return false;

		//Find the nearest intersection
		float x = sqrt(sphere->Radius * sphere->Radius - y * y);
		*t = *t - x;

		if (*t < 0.0f)
		{
			*t = *t + x;
			if (*t < 0.0f)
				return false;
		}

		return true;
	}

	__device__ Vector3 GenerateDirection(const uint16_t x, const uint16_t y, const uint16_t sizeX, const uint16_t sizeY)
	{
		Vector3 ndc;
		ndc.x = (x + 0.5f) / static_cast<float>(sizeX);
		ndc.y = (y + 0.5f) / static_cast<float>(sizeY);

		Vector3 pixel;
		pixel.x = (2.0f * ndc.x - 1.0f) * (static_cast<float>(sizeX) / sizeY) * tan(Radians(45.0f / 2.0f));
		pixel.y = (1.0f - 2.0f * ndc.y) * tan(Radians(45.0f / 2.0f));
		pixel.z = -1.0f;

		return Normalize(pixel);
	}

	__global__ void FillPixel(Sphere* sphere, Vector3* cameraPosition, const uint16_t sizeX, const uint16_t sizeY, Vector3* framebuffer)
	{
		uint16_t x = (blockIdx.x * blockDim.x) + threadIdx.x;
		uint16_t y = (blockIdx.y * blockDim.y) + threadIdx.y;

		Ray ray;
		ray.Origin	  = *cameraPosition;
		ray.Direction = GenerateDirection(x, y, sizeX, sizeY);

		float t = INFINITY;

		if (Intersection(sphere, ray, &t))
			framebuffer[x + y * sizeX] = Vector3(1.0f, 0.2f, 0.2f);
		else
			framebuffer[x + y * sizeX] = Vector3(0.5f, 0.5f, 0.5f);
	}

	void Render(Sphere* sphere, Vector3 cameraPosition, const uint16_t sizeX, const uint16_t sizeY, Vector3* frameBuffer)
	{
		dim3 threadsPerBlock(16, 16);
		dim3 numBlocks(sizeX / threadsPerBlock.x, sizeY / threadsPerBlock.y);

		Vector3*	d_Framebuffer;
		Vector3*	d_CameraPos;
		Sphere*		d_Sphere;

		cudaMalloc(reinterpret_cast<void**>(&d_Sphere), sizeof(Sphere));
		cudaMalloc(reinterpret_cast<void**>(&d_Framebuffer), sizeof(Vector3) * sizeX * sizeY);
		cudaMalloc(reinterpret_cast<void**>(&d_CameraPos), sizeof(Vector3));

		cudaMemcpy(d_Sphere, sphere, sizeof(Sphere), cudaMemcpyHostToDevice);
		cudaMemcpy(d_CameraPos, &cameraPosition, sizeof(Vector3), cudaMemcpyHostToDevice);

		FillPixel<<<numBlocks, threadsPerBlock>>>(d_Sphere, d_CameraPos, sizeX, sizeY, d_Framebuffer);

		cudaMemcpy(frameBuffer, d_Framebuffer, sizeof(Vector3) * sizeX * sizeY, cudaMemcpyDeviceToHost);

		cudaFree(d_Framebuffer);
		cudaFree(d_CameraPos);
		cudaFree(d_Sphere);

		size_t freeBytes;
		size_t totalBytes;
		cudaMemGetInfo(&freeBytes, &totalBytes);
		fprintf(stderr, "Used: %f, Free: %f\n", (float)freeBytes, (float)totalBytes);
	}
}

//int main()
//{
//	uint16_t sizeX = 1280;
//	uint16_t sizeY = 720;
//	
//	cuda::Sphere sphere = { cuda::Vector3(0.0f, 0.0f, -10.0f), 2.5f };
//	cuda::Vector3* Framebuffer = new cuda::Vector3[sizeX * sizeY];
//
//	cuda::Vector3 cp(10.0f, 10.0f, 10.f);
//
//	cuda::Render(&sphere, cp, sizeX, sizeY, Framebuffer);
//
//	//Write to file
//	std::ofstream outFile;
//	outFile.open("out.ppm");
//	if (!outFile.is_open())
//		return -1;
//
//	outFile << "P6\n" << sizeX << " " << sizeY << "\n255\n";
//	for (int i = 0; i < sizeX * sizeY; ++i)
//	{
//		outFile << (char)(255.0f * std::fmaxf(0.0f, std::fminf(1.0f, Framebuffer[i].x)));
//		outFile << (char)(255.0f * std::fmaxf(0.0f, std::fminf(1.0f, Framebuffer[i].y)));
//		outFile << (char)(255.0f * std::fmaxf(0.0f, std::fminf(1.0f, Framebuffer[i].z)));
//	}
//
//	return 0;
//}