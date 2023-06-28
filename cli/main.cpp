
#include "camera.hpp"
#include "qhy.hpp"

#include <spdlog/spdlog.h>


std::unique_ptr<Camera> getCamera() {

    std::vector<CameraId> cameraIds = scanCameras();
    if (cameraIds.empty()) {
        spdlog::error("No cameras found; aborting.");
        throw std::runtime_error("No cameras found; aborting.");
    }
    for (const auto& id : cameraIds) {
        spdlog::info("Found camera: {}", id.data());
    }

    auto camera = std::make_unique<Camera>(cameraIds[0].data());

    return camera;
}


int main(int, char**) {

    spdlog::set_level(spdlog::level::trace);

    init();
    std::unique_ptr<Camera> camera = getCamera();

    // camera->setFilterWheelPosition(3);
    // camera->waitFilterWheel();

    // camera->setFilterWheelPosition(0);
    // // camera->waitFilterWheel();

    // camera->startTemperatureControl(0);
    // for (size_t i = 0; i < 100; i++) {
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    //     double temp = camera->getTemperature();
    //     double pwm = camera->getTecPwm();
    //     spdlog::debug("Sensors: {} {}", temp, pwm);
    // }

    camera->setBinMode(BinMode::BIN_1x1);
    camera->setRoi({0, 0, 100, 100});
    std::this_thread::sleep_for(std::chrono::seconds(120));
    // camera->setBinMode(BinMode::BIN_2x2);
    // std::this_thread::sleep_for(std::chrono::seconds(10));
    // camera->setBinMode(BinMode::BIN_3x3);
    // std::this_thread::sleep_for(std::chrono::seconds(10));
    // camera->setBinMode(BinMode::BIN_4x4);
    // std::this_thread::sleep_for(std::chrono::seconds(10));

    camera = {};
    deinit();

    return 0;
}
