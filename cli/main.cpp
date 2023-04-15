#include "camera.hpp"
#include "qhy.hpp"
#include "qhyccd.h"
#include "spdlog/spdlog.h"

// TODO QHY doesn't actually say how long a buffer is needed!
constexpr size_t QHY_ID_BUFFER_LEN = 256;


int main(int, char**) {

    spdlog::set_level(spdlog::level::trace);
    SetQHYCCDLogLevel(0);

    QHYRet ret;

    // Initialize the library
    ret = InitQHYCCDResource();
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Failed to initialize QHY SDK.");
        throw std::runtime_error("Failed to initialize QHY SDK.");
    }

    // Identify cameras
    uint32_t cameraCount = ScanQHYCCD();
    if (cameraCount == 0) {
        spdlog::error("No cameras found.");
        throw std::runtime_error("No cameras found.");
    }
    spdlog::debug("Found {} camera(s).", cameraCount);

    // Enumerate cameras
    std::vector<std::array<char, QHY_ID_BUFFER_LEN>> cameraIDs;
    cameraIDs.resize(cameraCount);
    for (size_t i = 0; i < cameraCount; i++) {
        ret = GetQHYCCDId(i, cameraIDs[i].data());
        if (ret != QHYCCD_SUCCESS) {
            spdlog::error("Unable to get camera ID for index {}.", i);
            throw std::runtime_error("Unable to get camera ID.");
        }
        spdlog::debug("Found camera with ID:{}", cameraIDs[i].data());
    }

    spdlog::debug("Selected camera with ID:{}", cameraIDs[0].data());

    Camera camera(cameraIDs[0].data());

    camera.setExposureUs(1000000);

    // camera.doThing();
    // camera.doThing();
    // camera.doThing();
    // camera.doThing();
    // camera.doThing();

    // camera.doOtherThing();

    camera.temperatureThing();

    ret = ReleaseQHYCCDResource();
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Failed to release QHY SDK");
        throw std::runtime_error("Failed to release QHY SDK");
    }

    return 0;
}
