#include <Windows.h>
#include <math.h>
#include "Vector3.cpp"
#include "Matrix4.cpp"
#include "GLBindings/GLBindings.cpp"
#include "Window.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Shader.cpp"
#include "Render.cpp"

bool IsKeyDown(int key);
int APIENTRY WinMain(HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine, int cmdShow)
{
    Window::Create(instance, "rote_cube");

    CreateGLBindings();

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    Render::Create();
    int dir = -1;
    bool isRunning = true;
    while (isRunning)
    {
        MSG msg = {};
        while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) isRunning = false;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);  
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if(IsKeyDown(0x1B)) //esc
        {
            Window::Close();
        }
        if (IsKeyDown(0x41)) //a
        {
            dir = -1;
        }
        if (IsKeyDown(0x44)) //d
        {
            dir = 1;
        }
        if(IsKeyDown(0x20))//spce
		{
			dir = 0;
		}
        Render::Draw(dir);
        Window::SwapBuffers();
    }

    Render::Release();
    Window::Release();

    return 0;
}
bool IsKeyDown(int key) {
    return (GetKeyState((unsigned int)key) >> 1);
}
