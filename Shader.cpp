void* LoadFile(const char* path)
{

    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << path << std::endl;
        return nullptr;
    }
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    void* buffer = malloc(fileSize);
    if (!buffer)
    {
        std::cerr << "Error: Could not allocate memory for file buffer" << std::endl;
        return nullptr;
    }
    if (!file.read(static_cast<char*>(buffer), fileSize))
    {
        std::cerr << "Error: Could not read file " << path << std::endl;
        free(buffer);
        return nullptr;
    }
    file.close();

    return buffer;
}

unsigned int LoadShader(const char* shaderPath)
{
    unsigned int handle = glCreateProgram();

    void* shaderBuffer = LoadFile(shaderPath);
    if (!shaderBuffer)
    {
        std::cerr << "Error: Failed to load shader file" << std::endl;
        return 0;
    }
    const char* shaderSource = (const char*)shaderBuffer;

    std::istringstream shaderStream(shaderSource);
    std::string line;
    std::stringstream vertexShaderStream, fragmentShaderStream;
    std::stringstream* currentStream = nullptr;

    while (std::getline(shaderStream, line))
    {
        if (line.find("#shader vertex") != std::string::npos)
        {
            currentStream = &vertexShaderStream;
        }
        else if (line.find("#shader fragment") != std::string::npos)
        {
            currentStream = &fragmentShaderStream;
        }
        else if (currentStream)
        {
            (*currentStream) << line << '\n';
        }
    }

    std::string vertexShaderSource = vertexShaderStream.str();
    std::string fragmentShaderSource = fragmentShaderStream.str();

    const char* vertexShaderCode = vertexShaderSource.c_str();
    const char* fragmentShaderCode = fragmentShaderSource.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, 0);
    glCompileShader(vertexShader);
    glAttachShader(handle, vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, 0);
    glCompileShader(fragmentShader);
    glAttachShader(handle, fragmentShader);

    glLinkProgram(handle);

    glDetachShader(handle, vertexShader);
    glDeleteShader(vertexShader);
    glDetachShader(handle, fragmentShader);
    glDeleteShader(fragmentShader);

    free(shaderBuffer);

    return handle;
}
