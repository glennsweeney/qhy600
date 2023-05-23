
#include "application.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

#include <cstdio>
#include <spdlog/spdlog.h>


static void glfw_error_callback(int error, const char* description) {
    spdlog::error("Glfw Error {}: {}", error, description);
}

Application::Application() {

    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        spdlog::error("Unable to initialze GLFW.");
        throw std::runtime_error("Unable to initialize GLFW.");
    }
    spdlog::debug("GLFW initialized.");

    // GL 3.0 + GLSL 130
    const char* glslVersion = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window with graphics context
    _window = glfwCreateWindow(1280, 720, "QHY", NULL, NULL);
    if (_window == NULL) {
        spdlog::error("Unable to open a window.");
        throw std::runtime_error("Unable to open a window.");
    }
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);  // Enable vsync
    spdlog::debug("Window initialized.");

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init(glslVersion);
    spdlog::debug("ImGui initialized.");

    // Setup QHYCCD
    init();

    _cameraScanThread = std::thread([&]() {
        spdlog::debug("Beginning camera scan.");
        _cameras = scanCameras();
        spdlog::debug("Finished camera scan.");
    });
}

Application::~Application() {
    _cameraScanThread.join();
    _cameras.clear();
    deinit();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Application::run() {
    spdlog::debug("Entering main loop.");
    constexpr ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    while (!glfwWindowShouldClose(_window)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui
        // wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main
        // application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main
        // application, or clear/overwrite your copy of the keyboard data. Generally you may always
        // pass all inputs to dear imgui, and hide them from your application based on those two
        // flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You
        // can browse its code to learn more about Dear ImGui!).
        if (_showImguiDemoWindow)
            ImGui::ShowDemoWindow(&_showImguiDemoWindow);

        if (_showImplotDemoWindow)
            ImPlot::ShowDemoWindow(&_showImplotDemoWindow);

        _drawMainWindow();

        // Rendering
        ImGui::Render();
        int displayWidth, displayHeight;
        glfwGetFramebufferSize(_window, &displayWidth, &displayHeight);
        glViewport(0, 0, displayWidth, displayHeight);
        glClearColor(
                clearColor.x * clearColor.w,
                clearColor.y * clearColor.w,
                clearColor.z * clearColor.w,
                clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(_window);
    }
    spdlog::debug("Main loop exited.");
}

void Application::_drawMainWindow() {
    if (!_showMainWindow) {
        return;
    }

    if (!ImGui::Begin("Main Window", &_showMainWindow)) {
        ImGui::End();
        return;
    }

    ImGui::Text("Hello, world!");
    ImGui::End();
}
