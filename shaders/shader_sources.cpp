#include "shader_sources.h"
#include <glad/gl.h>

const GLchar* basic_vertex_src = 
R"glsl(#version 330 core

in vec2 position;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
})glsl";


const GLchar* basic_fragment_src = 
R"glsl(#version 330 core

out vec4 outColor;

void main()
{
    outColor = vec4(1.0, 1.0, 1.0, 1.0);
})glsl";