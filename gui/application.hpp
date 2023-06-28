#pragma once

#include "camera.hpp"

#include <GLFW/glfw3.h>
#include <atomic>
#include <thread>

class Application {

public:

    Application();
    ~Application();

    void run();

private:

    std::atomic<bool> _shouldClose = false;


    void _drawMainWindow();
    bool _showMainWindow = true;
    std::thread _cameraScanThread;
    std::vector<Camera> _cameras;
    std::atomic<ssize_t> _cameraIndex = -1;
    size_t _gain = 26;
    size_t _exposure = 1000;
    size_t _offset = 30;

    // Live view
    std::thread _liveViewThread;
    std::atomic<bool> _liveViewLive = false;

    void _drawTemperatureWindow();
    bool _showTemperatureWindow = true;
    std::thread _temperatureAdjustThread;
    std::atomic<bool> _temperatureControlEnabled = true;
    std::atomic<double> _targetTemperature = 0.0;
    std::atomic<double> _currentTemperature = 0.0;
    std::atomic<double> _currentTecPwm = 0.0;

    bool _showImguiDemoWindow = true;
    bool _showImplotDemoWindow = true;

    GLFWwindow* _window;
};
