#version 330 core
layout(location=0) in vec3 pos;
layout(location=1) in vec4 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

out vec4 outColor;

void main()
{
    gl_Position = project * view * model * vec4(pos,1.0);
    outColor = Color;
}
