#pragma once

#include "qhyccd.h"

#include <atomic>
#include <mutex>
#include <spdlog/fmt/bundled/format.h>
#include <string>
#include <thread>

enum class BinMode {
    BIN_1x1,
    BIN_2x2,
    BIN_3x3,
    BIN_4x4,
};

struct Roi {
    uint32_t startX;
    uint32_t startY;
    uint32_t sizeX;
    uint32_t sizeY;
};

template<>
struct fmt::formatter<Roi> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.end();
    }

    template<typename FormatContext>
    auto format(const Roi& input, FormatContext& ctx) -> decltype(ctx.out()) {
        return format_to(
                ctx.out(),
                "(startX={}, startY={}, sizeX={}, sizeY={})",
                input.startX,
                input.startY,
                input.sizeX,
                input.sizeY);
    }
};

class Frame {};

using FrameCallback = std::function<void(Frame&&)>;

struct CameraStats {
    std::vector<std::string> readModes;
    Roi sensorArea;
    Roi effectiveArea;
    Roi overscanArea;
    std::pair<double, double> sensorSize;
    std::pair<double, double> pixelSize;
    uint32_t nativeBits;
};

class Camera {

public:

    Camera(char* const cameraID);
    ~Camera();

    Camera(const Camera& rhs) = delete;
    Camera& operator=(const Camera& rhs) = delete;
    Camera(Camera&& rhs) = delete;
    Camera& operator=(Camera&& rhs) = delete;

    void setGain(size_t gain);
    void setOffset(size_t offset);
    void setExposure(size_t exposure);
    void setBinMode(BinMode mode);
    void setRoi(const Roi& roi);

    void setFilterWheelPosition(size_t position);
    void waitFilterWheel();

    void startTemperatureControl(double targetTemperature);
    void stopTemperatureControl();
    bool isTemperatureStabilized(double threshold = 2.0);

    const std::string& getCameraID();

    double getTemperature();
    double getTecPwm();
    Roi getRoi();

    void registerFrameCallback(FrameCallback callback);


    // old


    void exposeSingle();
    void writeBuffer(const std::string& filepath);

    void startLive();
    void thingy();
    void endLive();


private:

    // Camera info
    std::string _cameraID;
    qhyccd_handle* _cameraHandle = nullptr;
    CameraStats _stats;

    // Exposure info
    double _gain;
    double _offset;
    double _exposure;

    // ROI info
    BinMode _binMode;
    Roi _roi;

    // Filter control
    size_t _filterPosition;
    std::atomic<bool> _filterMoving = false;
    std::thread _filterMovingThread;

    // Temperature control
    double _targetTemperature;
    std::atomic<bool> _temperatureControlActive = false;
    std::thread _temperatureControlThread;

    // Frame streaming
    uint32_t _memLength;
    FrameCallback _frameCallback = nullptr;
    std::atomic<bool> _shouldStream = true;
    std::thread _frameStreamThread;
    void _startStream();

    std::vector<uint8_t> _framebuffer;
};
