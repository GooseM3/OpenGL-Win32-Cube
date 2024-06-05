#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 Normal;

uniform mat4 u_viewProjectionMatrix;

void main()
{
    Normal = normal;
    gl_Position = u_viewProjectionMatrix * vec4(position, 1.0);
}


#shader fragment

#version 330 core

in vec3 Normal;
out vec4 Color;

const vec3 Albedo = vec3(1.0, 0.0, 0.0);
const vec3 LightDirection = vec3(4.0, -5.0, -3.5);

void main()
{
    vec3 n = normalize(Normal);
    vec3 l = normalize(-LightDirection);

    float nDotL = max(dot(n, l), 0.0);

    vec3 color = Albedo * nDotL;

    Color = vec4(color, 1.0);
}

/*
#version 330 core

in vec3 Normal;
out vec4 Color;

uniform float time;

const vec3 LightDirection = vec3(4.0, -5.0, -3.5);

void main()
{
    vec3 n = normalize(Normal);
    vec3 l = normalize(-LightDirection);

    float nDotL = max(dot(n, l), 0.0);

    // Change Albedo color over time
    vec3 Albedo = vec3(abs(sin(time)), abs(sin(time + 2.0)), abs(sin(time + 4.0)));
    vec3 color = Albedo * nDotL;

    Color = vec4(color, 1.0);
}*/
