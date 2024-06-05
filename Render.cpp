namespace Renderer
{
    unsigned int vaoHandle;
    unsigned int vboHandle;
    unsigned int iboHandle;

    unsigned int shaderHandle;
    int viewProjectionMatrixLocation;
    int timeLocation;

    LARGE_INTEGER frequency; // For storing the frequency of the performance counter
    LARGE_INTEGER startTime; // For storing the start time

    void InitializeTimer()
    {
        // Get the frequency of the performance counter
        QueryPerformanceFrequency(&frequency);
        // Get the current value of the performance counter
        QueryPerformanceCounter(&startTime);
    }

    float GetElapsedTime()
    {
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        // Calculate the elapsed time in seconds
        return static_cast<float>(currentTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
    }
    
    void Release()
    {
        glDeleteVertexArrays(1, &vaoHandle);
        glDeleteBuffers(1, &iboHandle);
        glDeleteBuffers(1, &vboHandle);
        glDeleteProgram(shaderHandle);
    }

    float cubeVertices[] =
    {
        -1.f,  1.f, 1.f, -1.f, 0.f, 0.f,
        -1.f,  1.f, 1.f, 0.f, 1.f, 0.f,
        -1.f,  1.f, 1.f, 0.f, 0.f, 1.f,

         1.f, 1.f, 1.f,  1.f, 0.f, 0.f,
         1.f, 1.f, 1.f,  0.f, 1.f, 0.f,
         1.f, 1.f, 1.f,  0.f, 0.f, 1.f,

         1.f, -1.f, 1.f,  1.f, 0.f, 0.f,
         1.f, -1.f, 1.f,  0.f, -1.f, 0.f,
         1.f, -1.f, 1.f,  0.f, 0.f, 1.f,

         -1.f, -1.f, 1.f,  -1.f, 0.f, 0.f,
         -1.f, -1.f, 1.f,  0.f, -1.f, 0.f,
         -1.f, -1.f, 1.f,  0.f, 0.f, 1.f,

         -1.f, 1.f, -1.f,  -1.f, 0.f, 0.f,
         -1.f, 1.f, -1.f,  0.f, 1.f, 0.f,
         -1.f, 1.f, -1.f,  0.f, 0.f, -1.f,

         1.f, 1.f, -1.f,  1.f, 0.f, 0.f,
         1.f, 1.f, -1.f,  0.f, 1.f, 0.f,
         1.f, 1.f, -1.f,  0.f, 0.f, -1.f,

         1.f, -1.f, -1.f,  1.f, 0.f, 0.f,
         1.f, -1.f, -1.f,  0.f, -1.f, 0.f,
         1.f, -1.f, -1.f,  0.f, 0.f, -1.f,

         -1.f, -1.f, -1.f,  -1.f, 0.f, 0.f,
         -1.f, -1.f, -1.f,  0.f, -1.f, 0.f,
         -1.f, -1.f, -1.f,  0.f, 0.f, -1.f

    };

    unsigned int cubeIndices[] =
    {
        2, 11, 8, 
        2, 8, 5,

        14, 20, 23, 
        14, 17, 20,

        13, 1, 4,
        13 , 4 , 16,

        10, 22, 19,
        10, 19, 7,

        12, 21, 9, 
        12, 9, 0,

        3, 6, 18, 
        3, 18, 15
    };
    void Create()
    {
        glGenVertexArrays(1, &vaoHandle);
        glBindVertexArray(vaoHandle);
        glGenBuffers(1, &vboHandle);
        glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
        glGenBuffers(1, &iboHandle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 6, 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(float) * 6, (void*)(sizeof(float) * 3));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        shaderHandle = LoadShader("../cube.shader");
        viewProjectionMatrixLocation = glGetUniformLocation(shaderHandle, "u_viewProjectionMatrix");
        timeLocation = glGetUniformLocation(shaderHandle, "time");

        InitializeTimer(); 
    }

    void Draw(int dir)
    {
        glUseProgram(shaderHandle);

        float fov = 3.14159265f * 0.25f;//pi
        Matrix4 projectionMatrix = Matrix4::CreatePerspectiveFieldOfView(fov, Window::aspectRatio, 0.1f, 10.0f);
        float elapsedTime = 0.25f * GetElapsedTime();
        float radius = 5.0f;
        float camX = sin(elapsedTime) * radius * dir;
        float camZ = cos(elapsedTime) * radius;
        if (dir == 0)
        {
            camX = 0;
            camZ = 0;
        }
        Vector3 cameraPos = Vector3{ camX,  4.0f, camZ };

        Matrix4 viewMatrix = Matrix4::LookAt(cameraPos, Vector3{ 0.0f, 0.0f, 0.0f });
        Matrix4 viewProjectionMatrix = projectionMatrix * viewMatrix;
        glUniformMatrix4fv(viewProjectionMatrixLocation, 1, false, &viewProjectionMatrix.row0X);

        glUniform1f(timeLocation, elapsedTime);

        glBindVertexArray(vaoHandle);
        glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
    }
}