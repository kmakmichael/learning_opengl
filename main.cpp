#include <stdio.h>
#include <string>
#include <fstream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "shaders/shader_sources.h"

static void error_callback(int error, const char* desc) {
    fprintf(stderr, "Error %s\n", desc);
}

static void closewindow_callback(GLFWwindow* w)
{
    printf("closing window\n");
}

static GLuint read_shader(GLenum shader_type, const char* shader_src) {
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_src, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        fprintf(stderr, "Shader failed to compile:\n%s\n", buffer);
        return 0;
    }
    printf("Loaded shader\n");
    return shader;
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "GLFW failed to initialize");
        return -1;
    }
    glfwSetErrorCallback(error_callback);

    // specify OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(640, 480, "test", NULL, NULL);

    if (!window) {
        fprintf(stderr, "Failed to create window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    int version = gladLoadGL(glfwGetProcAddress);
    printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    glfwSetWindowCloseCallback(window, closewindow_callback);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLfloat vertices[] = {
        1.0, 1.0, 1.0,
        1.0, 1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0, -1.0, 1.0,
        -1.0, -1.0, 1.0,
        -1.0, -1.0, -1.0,
        -1.0, 1.0, -1.0,
        -1.0, 1.0, 1.0
    };
    GLuint wireframe_cube[] = {
        0,1,
        1,2,
        2,3,
        3,4,
        4,5,
        5,6,
        6,7,
        0,3,
        4,7,
        0,7,
        1,6,
        2,5
    };
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(wireframe_cube), wireframe_cube, GL_STATIC_DRAW);

    GLuint vertex_shader = read_shader(GL_VERTEX_SHADER, model_vertex_src);
    GLuint fragment_shader = read_shader(GL_FRAGMENT_SHADER, basic_fragment_src);    
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glUseProgram(shader_program);

    GLint posAttrib = glGetAttribLocation(shader_program, "position");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    GLfloat rotation[] = {45.0f, 45.0f, 0.0f};
    GLint rotationAttrib = glGetUniformLocation(shader_program, "rotation");
    glUniform3f(rotationAttrib, rotation[0], rotation[1], rotation[2]);

    GLfloat scale[] = {0.4, 0.4, 0.4};
    GLint scaleAttrib = glGetUniformLocation(shader_program, "scale");
    glUniform3f(scaleAttrib, scale[0], scale[1], scale[2]);

    glClearColor(0.04f, 0.04f, 0.02f, 1.0f);
    while (!glfwWindowShouldClose(window)) {
        glfwSwapInterval(1);
        glClear(GL_COLOR_BUFFER_BIT);
        rotation[2] += 1;
        glUniform3f(rotationAttrib, rotation[0], rotation[1], rotation[2]);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}