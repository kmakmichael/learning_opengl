#include <stdlib.h>
#include <stdio.h>

#include <GLFW/glfw3.h>

static void error_callback(int error, const char* desc) {
    fprintf(stderr, "Error %s\n", desc);
}

int main(void) {
    if (!glfwInit()) {
        printf("initialization failed\n");
        return -1;
    }
    printf("initialization successful\n");

    glfwTerminate();
    return 0;
}