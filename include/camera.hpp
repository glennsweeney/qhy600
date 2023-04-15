#pragma once

#include "qhyccd.h"

#include <string>

class Camera {
public:
    Camera(char* const cameraID);

    ~Camera();

    void setExposureUs(size_t us);

    void doThing();

    void doOtherThing();

    void temperatureThing();

private:

    const std::string _cameraID;
    qhyccd_handle* _cameraHandle = nullptr;

    std::vector<uint8_t> _framebuffer;
};
