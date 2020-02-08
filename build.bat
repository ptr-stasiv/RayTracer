@echo off
cd bin
g++ ..\src\main.cpp ..\src\graphics\window\window.cpp ..\src\graphics\shaders\shader_manager.cpp ..\src\core\camera\camera.cpp ..\src\core\shapes\sphere.cpp ..\src\input\input.cpp -o RayTracer -I ..\extern\x86\GLFW\include -I ..\extern\x86\GLEW\include -I ..\extern\glm -L ..\extern\x86\GLFW\lib -L ..\extern\x86\GLEW\lib -lglfw3 -lglew32s -lopengl32 -lgdi32
