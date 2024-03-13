#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "render/Renderer.h"
#include "render/VertexBuffer.h"
#include "render/IndexBuffer.h"
#include "render/VertexArray.h"
#include "render/VertexBufferLayout.h"
#include "render/Shader.h"
#include "render/Texture.h"
#include "Core.h"
#include "GameTime.h"
#include "AppWindow.h"
#include "Input.h"
#include "audio/SoundEngine.h"
#include "render/ShaderManager.h"
#include "render/FontManager.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imconfig.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


#include "OpenGLTraining.h"


int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    AppWindow::WindowHeight = 540;
    AppWindow::WindowWidth = 960;
    window = glfwCreateWindow(AppWindow::WindowWidth, AppWindow::WindowHeight, "Space Invaders", NULL, NULL);

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

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    std::cout << glGetString(GL_VERSION) << std::endl;

    // Set OpenGL behaviour for handling transparency and enable it
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Setup Platform/Renderer backends
    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //ImGui_ImplGlfw_InitForOpenGL(window, true);
    //ImGui_ImplOpenGL3_Init(glsl_version);
    //ImGui::StyleColorsDark();

    SoundEngine soundEngine{};

    Shader spriteShader = ShaderManager::LoadShader("res/shaders/sprite.vs", "res/shaders/sprite.frag", nullptr, "sprite");
    Shader textShader = ShaderManager::LoadShader("res/shaders/text_2d.vs", "res/shaders/text_2d.fs", nullptr, "text");
    textShader.Bind();
    textShader.SetUniformMat4f("projection", glm::ortho(0.0f, static_cast<float>(AppWindow::WindowWidth), static_cast<float>(AppWindow::WindowHeight), 0.0f));
    textShader.SetUniform1i("text", 0);

    FontManager::CreateFont("default", "res/fonts/Roboto-Bold.ttf", 12);

    Core core{};
    core.Awake();
    core.Start();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        const float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        GameTime::Time = currentFrame;
        GameTime::DeltaTime = deltaTime;

        GLCall(glClear(GL_COLOR_BUFFER_BIT));

       /* ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();*/

        core.UpdateInput();
        core.UpdatePhysics();
        core.Update();
        core.Render();

        //ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();

        core.PostRenderUpdate();
    }

    //ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            Input::SetKeyStatus(key, true);
        }

        else if (action == GLFW_RELEASE)
        {
            Input::SetKeyStatus(key, false);
        }
    }
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}