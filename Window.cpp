namespace Window
{
    int width;
    int height;
    float aspectRatio;

    HDC deviceContext;
    HGLRC glContext;

    LRESULT CALLBACK WindowProc(HWND window, UINT uMsg, WPARAM wParam, LPARAM lParam){
        switch (uMsg)
        {
        case WM_SIZE:
            width = LOWORD(lParam);
            height = HIWORD(lParam);
            aspectRatio = (float)width / height;
            glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
            break;
        case WM_CLOSE:
            DestroyWindow(window);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(window, uMsg, wParam, lParam);
        }
        return 0;
    }

    int Create(HINSTANCE instance, const char* title){
        WNDCLASSEX wc = {};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = instance;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.lpszClassName = "wc";

        RegisterClassEx(&wc);
        if (RegisterClassEx(&wc)){
            MessageBox(NULL, "Window Registration Failed!", "Error!",
                MB_ICONEXCLAMATION | MB_OK);
            return 0;
        }
        HWND hwnd;
        hwnd = CreateWindowEx(0, wc.lpszClassName, title, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, instance, NULL);
        deviceContext = GetDC(hwnd);

        PIXELFORMATDESCRIPTOR pfd = {sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 24, 0, 0, 0, 0, 0, 0, 0,  0,0, 0, 0, 0, 0, 32,0,0,PFD_MAIN_PLANE, 0,0, 0, 0 };
         HDC  hdc;
         int  iPixelFormat;
        iPixelFormat = ChoosePixelFormat(hdc, &pfd);
        SetPixelFormat(hdc, iPixelFormat, &pfd);
        int pixelFormatIndex = ChoosePixelFormat(deviceContext, &pfd);
        PIXELFORMATDESCRIPTOR pixelFormat;
        DescribePixelFormat(deviceContext, pixelFormatIndex, sizeof(pixelFormat), &pixelFormat);
        SetPixelFormat(deviceContext, pixelFormatIndex, &pixelFormat);

        glContext = wglCreateContext(deviceContext);
        wglMakeCurrent(deviceContext, glContext);

        glClearColor(.85f, .85f, .85f, 1.0f);
    }

    void Release(){
        wglDeleteContext(glContext);
    }

    void SwapBuffers(){
        SwapBuffers(deviceContext);
    }
    void Close() {
        PostQuitMessage(0);
    }
}
