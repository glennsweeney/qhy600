#include "qhy.hpp"

#include <spdlog/spdlog.h>


void init() {

    spdlog::debug("Initializing QHY SDK.");
    EnableQHYCCDMessage(false);


    // Initialize the library
    QHYRet ret = InitQHYCCDResource();
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Failed to initialize QHY SDK.");
        throw std::runtime_error("Failed to initialize QHY SDK.");
    }
}


void deinit() {
    spdlog::debug("Releasing QHY SDK.");
    QHYRet ret = ReleaseQHYCCDResource();
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Failed to release QHY SDK");
        throw std::runtime_error("Failed to release QHY SDK");
    }
}


std::vector<CameraId> scanCameras() {

    // Identify cameras
    uint32_t cameraCount = ScanQHYCCD();
    if (cameraCount == 0) {
        spdlog::error("No cameras found.");
        throw std::runtime_error("No cameras found.");
    }
    spdlog::info("Found {} camera(s).", cameraCount);

    // Enumerate cameras
    std::vector<CameraId> cameraIds;
    cameraIds.reserve(cameraCount);

    for (size_t i = 0; i < cameraCount; i++) {
        CameraId cameraId;
        QHYRet ret = GetQHYCCDId(i, cameraId.data());
        if (ret != QHYCCD_SUCCESS) {
            spdlog::error("Unable to get camera ID for index {}.", i);
            throw std::runtime_error("Unable to get camera ID.");
        }
        spdlog::debug("Found camera with ID:{}", cameraId.data());
        cameraIds.push_back(std::move(cameraId));
    }

    return cameraIds;
}
