#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imconfig.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "OpenGLTraining.h"


int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error initiating GLEW";
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
             0.0f, 0.0f, 0.0f, 0.0f, // 0 // Bottom left vertex
             100.0f, 0.0f, 1.0f, 0.0f, // 1 // Bottom right
             100.0f, 100.0f, 1.0f, 1.0f, // 2 // Top right
             0.0f, 100.0f, 0.0f, 1.0f  // 3 // Top left
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Set OpenGL behaviour for handling transparency and enable it
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va{};
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2); // First 2 floats are positions
    layout.Push<float>(2); // Next 2 floats are UV (texture coordinates)
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    float leftBorder = 0.0f, rightBorder = 960.0f;
    float bottomBorder = 0.0f, topBorder = 540.0f;
    float zNear = -1.0f, zFar = 1.0f;
    glm::mat4 proj = glm::ortho(leftBorder, rightBorder, bottomBorder, topBorder, zNear, zFar);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

    Texture texture("res/textures/cool_texture.png");
    texture.Bind(); //must match with slot below
    shader.SetUniform1i("u_Texture", 0);
    

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    /*float r = 0;
    float increment = 0.05f;*/

    Renderer renderer;

    // Setup Platform/Renderer backends
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.0f);
    glm::vec3 translation(0, 0, 0);

    while (!glfwWindowShouldClose(window))
    {
        //GLCall(glClearColor(0.5f, 0.5f, 0.5f, 1.f)); //Set BG color
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        shader.Bind();
        //shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
        glm::mat4 mvp = proj * view * model;

        ImGuiTranslationExample(translation);

        shader.SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(va, ib, shader);

        /*if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;

        r += increment;*/

        //ImGuiExample(show_demo_window, show_another_window, clear_color, io);
        //ImGuiShowAnotherWindowExample(show_another_window);

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void ImGuiTranslationExample(glm::vec3& translation)
{
    ImGui::Begin("Hello, translations!");
    ImGui::SliderFloat("Translation X", &translation.x, 0.0f, 860.0f); //extracting 100 from screen values because of the object "size" on VertexBuffer
    ImGui::SliderFloat("Translation Y", &translation.y, 0.0f, 440.0f);
    ImGui::End();
}

void ImGuiShowAnotherWindowExample(bool& show_another_window)
{
    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }
}

void ImGuiExample(bool& show_demo_window, bool& show_another_window, ImVec4& clear_color, ImGuiIO& io)
{
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, demo options!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }
}
