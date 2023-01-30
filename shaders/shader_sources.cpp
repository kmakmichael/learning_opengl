#include "shader_sources.h"

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

const GLchar* model_vertex_src = 
R"glsl(#version 330 core

in vec3 position;
uniform vec3 rotation;
uniform vec3 scale;
uniform vec3 translation;

mat4x4 rotation_matrix(vec3 r);
mat4x4 model_matrix();

void main()
{
    gl_Position = model_matrix() * vec4(position, 1.0);
}

mat4x4 model_matrix()
{
    mat4x4 rm = rotation_matrix(radians(rotation));
    mat4x4 sm = mat4x4( scale.x, 0.0, 0.0, 0.0,
                        0.0, scale.y, 0.0, 0.0,
                        0.0, 0.0, scale.z, 0.0,
                        0.0, 0.0, 0.0, 1.0      );
    mat4x4 tm = mat4x4( 1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0,
                        translation, 1.0  );
    return tm * sm * rm;
}

mat4x4 rotation_matrix(in vec3 r)
{
    mat4x4 r_x = mat4x4(  1.0, 0.0, 0.0, 0.0,
                            0.0, cos(r.x), sin(r.x), 0.0,
                            0.0, -1*sin(r.x), cos(r.x), 0.0,
                            0.0, 0.0, 0.0, 1.0);
    mat4x4 r_y = mat4x4(  cos(r.y), 0.0, -1*sin(r.y), 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            sin(r.y), 0.0, cos(r.y), 0.0,
                            0.0, 0.0, 0.0, 1.0);
    mat4x4 r_z = mat4x4(  cos(r.z), sin(r.z), 0.0, 0.0,
                            -1*sin(r.z), cos(r.z), 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0);
    return r_x * r_y * r_z;
})glsl";