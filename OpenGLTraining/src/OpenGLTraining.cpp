#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
    std::cout << "Hello World!\n";

    glfwInit();

    GLFWwindow* window = glfwCreateWindow(800, 600, "window1", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) // Vai dar bom
    {
        std::cout << "Error initiating GLEW";
    }

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f); // No OpenGL matrix de projeção  é do -1f ao 1f em ambos eixos
        glVertex2f(0.f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}