@echo off
cd bin
E:\Apps\Dev\mingw\x64\bin\g++ -o1 ..\src\main.cpp ..\src\graphics\window\window.cpp ..\src\graphics\shaders\shader_manager.cpp ..\src\core\camera\camera.cpp ..\src\core\shapes\sphere.cpp ..\src\input\input.cpp -m64 -std=c++11  -o RayTracer -I ..\extern\x86\GLFW\include -I ..\extern\x86\GLEW\include -I ..\extern\glm -I ..\extern\rt_parallel\include -L ..\extern\x64\GLFW\lib -L ..\extern\x64\GLEW\lib -L. -lglfw3 -lglew32s -lopengl32 -lgdi32 -luser32 -lRT_Parallel
