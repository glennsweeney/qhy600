
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
    _cameraScanThread = std::thread([&]() {
        init();
        spdlog::debug("Beginning camera scan.");
        _cameras = scanCameras();
        spdlog::debug("Finished camera scan.");
        if (_cameras.size() > 0) {
            _cameraIndex = 0;
        } else {
            spdlog::warn("No camera found; UI remaining inactive.");
            _cameraIndex = -1;
            return;
        }

        _cameras[_cameraIndex].setGain(_gain);
        _cameras[_cameraIndex].setOffset(_offset);
        _cameras[_cameraIndex].setExposure(_exposure);
    });

    // Temperature monitor
    _temperatureAdjustThread = std::thread([&]() {
        while (!_shouldClose) {
            if (_cameraIndex < 0) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }
            _cameras[_cameraIndex].controlTemperature(_targetTemperature);
            _currentTemperature = _cameras[_cameraIndex].getTemperature();
            _currentTecPwm = _cameras[_cameraIndex].getTecPwm();
            spdlog::trace("Temperature: {}/{}", _currentTemperature, _currentTecPwm);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
}

Application::~Application() {
    _shouldClose = true;
    _cameraScanThread.join();
    _cameras.clear();

    // If we made it here, we know we called init().
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
        _drawTemperatureWindow();

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

    ImGui::Text("Camera ID: ");

    // Early exit if there's no active camera
    if (_cameraIndex < 0) {
        ImGui::End();
        return;
    }

    ImGui::SameLine();
    ImGui::Text("%s", _cameras[_cameraIndex].getCameraID().c_str());

    int gainInt = _gain;
    if (ImGui::SliderInt("Gain", &gainInt, 0, 200, "%d", ImGuiSliderFlags_AlwaysClamp)) {
        _gain = gainInt;
        spdlog::trace("Update Gain: {}", _gain);
        _cameras[_cameraIndex].setGain(_gain);
    }
    int offsetInt = _offset;
    if (ImGui::SliderInt("Offset", &offsetInt, 0, 255, "%d", ImGuiSliderFlags_AlwaysClamp)) {
        _offset = offsetInt;
        spdlog::trace("Update Offset: {}", _offset);
        _cameras[_cameraIndex].setOffset(_offset);
    }
    float exposureFloat = _exposure / 1e6f;
    if (ImGui::DragFloat(
                "Exposure Time",
                &exposureFloat,
                4.0,
                0.0,
                3600,
                "%0.4f",
                ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_Logarithmic)) {
        _exposure = exposureFloat * 1e6f;
        spdlog::trace("Update Exposure: {} ({})", exposureFloat, _exposure);
        _cameras[_cameraIndex].setExposure(_exposure);
    }

    if (ImGui::Button("C")) {
        _cameras[_cameraIndex].setFilterWheelPosition(0);
    }
    ImGui::SameLine();
    if (ImGui::Button("R")) {
        _cameras[_cameraIndex].setFilterWheelPosition(1);
    }
    ImGui::SameLine();
    if (ImGui::Button("G")) {
        _cameras[_cameraIndex].setFilterWheelPosition(2);
    }
    ImGui::SameLine();
    if (ImGui::Button("B")) {
        _cameras[_cameraIndex].setFilterWheelPosition(3);
    }

    if (ImGui::Button("Capture")) {
        _cameras[_cameraIndex].exposeSingle();
        _cameras[_cameraIndex].writeBuffer("test.png");
    }

    if (ImGui::Button("StartLive")) {
        _cameras[_cameraIndex].startLive();
        // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        // _liveViewLive = true;
        // _liveViewThread = std::thread([&]() {
        //     while (_liveViewLive) {
        //         _cameras[_cameraIndex].thingy();
        //     }
        // });
    }
    if (ImGui::Button("LiveCapture")) {
        _cameras[_cameraIndex].thingy();
    }
    if (ImGui::Button("EndLive")) {
        _cameras[_cameraIndex].endLive();
        _liveViewLive = true;
    }

    ImGui::End();
}

void Application::_drawTemperatureWindow() {
    if (!_showTemperatureWindow) {
        return;
    }

    if (!ImGui::Begin("Temperature Window", &_showTemperatureWindow)) {
        ImGui::End();
        return;
    }

    ImGui::Text("Temperature!");

    // Early exit if there's no active camera
    if (_cameraIndex < 0) {
        ImGui::End();
        return;
    }

    ImGui::Text("Current Temperature: ");
    ImGui::SameLine();
    ImGui::Text("%2.1f", _currentTemperature.load());

    ImGui::Text("Current PWM: ");
    ImGui::SameLine();
    ImGui::Text("%3.0f", _currentTecPwm.load());


    float targetTemp = _targetTemperature;
    ImGui::SliderFloat(
            "Target Temperature", &targetTemp, -40.0f, 40.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
    _targetTemperature = static_cast<double>(targetTemp);

    ImGui::End();
}
