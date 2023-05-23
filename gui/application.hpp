#pragma once

#include "camera.hpp"

#include <GLFW/glfw3.h>
#include <thread>

class Application {

public:

    Application();
    ~Application();

    void run();

private:

    bool _showMainWindow = true;
    void _drawMainWindow();

    GLFWwindow* _window;

    std::vector<Camera> _cameras;
    std::thread _cameraScanThread;

    bool _showImguiDemoWindow = true;
    bool _showImplotDemoWindow = true;
};
