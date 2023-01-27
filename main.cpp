#include <stdio.h>

#include <GLFW/glfw3.h>

static void error_callback(int error, const char* desc) {
    fprintf(stderr, "Error %s\n", desc);
}

static void closewindow_callback(GLFWwindow* w)
{
    printf("closing window\n");
}

int main(void) {
    if (!glfwInit()) {
        return -1;
    }
    glfwSetErrorCallback(error_callback);

    // specify some hints
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(640, 480, "test", NULL, NULL);

    if (!window) {
        fprintf(stderr, "failed to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowCloseCallback(window, closewindow_callback);
    // lock to display refresh rate
    glfwSwapInterval(1);
    glClearColor(0.04f, 0.04f, 0.02f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    glfwSwapBuffers(window);
    while (!glfwWindowShouldClose(window)) {
        glfwWaitEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}