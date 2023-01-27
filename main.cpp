#include <stdlib.h>
#include <stdio.h>

#include <GLFW/glfw3.h>

static void error_callback(int error, const char* desc) {
    fprintf(stderr, "Error %s\n", desc);
}

int main(void) {
    if (!glfwInit()) {
        return -1;
    }
    glfwSetErrorCallback(error_callback);

    // specify OpenGl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(640, 480, "test", NULL, NULL);
    if (!window) {
        fprintf(stderr, "failed to create window");
        glfwTerminate();
        return -1;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}