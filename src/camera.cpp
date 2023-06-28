#include "camera.hpp"

#include "qhy.hpp"
#include "spdlog/spdlog.h"

#include <chrono>
#include <cmath>
#include <png.h>
#include <string>
#include <thread>


void checkControl(qhyccd_handle* handle, CONTROL_ID id, const std::string& controlName) {
    QHYRet ret = IsQHYCCDControlAvailable(handle, id);
    spdlog::trace("Control {}: {}", controlName, ret == QHYCCD_SUCCESS ? "yes" : "no");
    if (ret == QHYCCD_SUCCESS) {
        double value = GetQHYCCDParam(handle, id);
        double min;
        double max;
        double step;
        GetQHYCCDParamMinMaxStep(handle, id, &min, &max, &step);
        spdlog::trace("\t{} [{}:{}:{}]", value, min, step, max);
    }
}


void checkControls(qhyccd_handle* handle) {
    checkControl(handle, CONTROL_BRIGHTNESS, "CONTROL_BRIGHTNESS");
    checkControl(handle, CONTROL_CONTRAST, "CONTROL_CONTRAST");
    checkControl(handle, CONTROL_WBR, "CONTROL_WBR");
    checkControl(handle, CONTROL_WBB, "CONTROL_WBB");
    checkControl(handle, CONTROL_WBG, "CONTROL_WBG");
    checkControl(handle, CONTROL_GAMMA, "CONTROL_GAMMA");
    checkControl(handle, CONTROL_GAIN, "CONTROL_GAIN");
    checkControl(handle, CONTROL_OFFSET, "CONTROL_OFFSET");
    checkControl(handle, CONTROL_EXPOSURE, "CONTROL_EXPOSURE");
    checkControl(handle, CONTROL_SPEED, "CONTROL_SPEED");
    checkControl(handle, CONTROL_TRANSFERBIT, "CONTROL_TRANSFERBIT");
    checkControl(handle, CONTROL_CHANNELS, "CONTROL_CHANNELS");
    checkControl(handle, CONTROL_USBTRAFFIC, "CONTROL_USBTRAFFIC");
    checkControl(handle, CONTROL_ROWNOISERE, "CONTROL_ROWNOISERE");
    checkControl(handle, CONTROL_CURTEMP, "CONTROL_CURTEMP");
    checkControl(handle, CONTROL_CURPWM, "CONTROL_CURPWM");
    checkControl(handle, CONTROL_MANULPWM, "CONTROL_MANULPWM");
    checkControl(handle, CONTROL_CFWPORT, "CONTROL_CFWPORT");
    checkControl(handle, CONTROL_COOLER, "CONTROL_COOLER");
    checkControl(handle, CONTROL_ST4PORT, "CONTROL_ST4PORT");
    checkControl(handle, CAM_COLOR, "CAM_COLOR");
    checkControl(handle, CAM_BIN1X1MODE, "CAM_BIN1X1MODE");
    checkControl(handle, CAM_BIN2X2MODE, "CAM_BIN2X2MODE");
    checkControl(handle, CAM_BIN3X3MODE, "CAM_BIN3X3MODE");
    checkControl(handle, CAM_BIN4X4MODE, "CAM_BIN4X4MODE");
    checkControl(handle, CAM_MECHANICALSHUTTER, "CAM_MECHANICALSHUTTER");
    checkControl(handle, CAM_TRIGER_INTERFACE, "CAM_TRIGER_INTERFACE");
    checkControl(handle, CAM_TECOVERPROTECT_INTERFACE, "CAM_TECOVERPROTECT_INTERFACE");
    checkControl(handle, CAM_SINGNALCLAMP_INTERFACE, "CAM_SINGNALCLAMP_INTERFACE");
    checkControl(handle, CAM_FINETONE_INTERFACE, "CAM_FINETONE_INTERFACE");
    checkControl(handle, CAM_SHUTTERMOTORHEATING_INTERFACE, "CAM_SHUTTERMOTORHEATING_INTERFACE");
    checkControl(handle, CAM_CALIBRATEFPN_INTERFACE, "CAM_CALIBRATEFPN_INTERFACE");
    checkControl(
            handle, CAM_CHIPTEMPERATURESENSOR_INTERFACE, "CAM_CHIPTEMPERATURESENSOR_INTERFACE");
    checkControl(handle, CAM_USBREADOUTSLOWEST_INTERFACE, "CAM_USBREADOUTSLOWEST_INTERFACE");
    checkControl(handle, CAM_8BITS, "CAM_8BITS");
    checkControl(handle, CAM_16BITS, "CAM_16BITS");
    checkControl(handle, CAM_GPS, "CAM_GPS");
    checkControl(handle, CAM_IGNOREOVERSCAN_INTERFACE, "CAM_IGNOREOVERSCAN_INTERFACE");
    checkControl(handle, QHYCCD_3A_AUTOEXPOSURE, "QHYCCD_3A_AUTOEXPOSURE");
    checkControl(handle, QHYCCD_3A_AUTOFOCUS, "QHYCCD_3A_AUTOFOCUS");
    checkControl(handle, CONTROL_AMPV, "CONTROL_AMPV");
    checkControl(handle, CONTROL_VCAM, "CONTROL_VCAM");
    checkControl(handle, CAM_VIEW_MODE, "CAM_VIEW_MODE");
    checkControl(handle, CONTROL_CFWSLOTSNUM, "CONTROL_CFWSLOTSNUM");
    checkControl(handle, IS_EXPOSING_DONE, "IS_EXPOSING_DONE");
    checkControl(handle, ScreenStretchB, "ScreenStretchB");
    checkControl(handle, ScreenStretchW, "ScreenStretchW");
    checkControl(handle, CONTROL_DDR, "CONTROL_DDR");
    checkControl(handle, CAM_LIGHT_PERFORMANCE_MODE, "CAM_LIGHT_PERFORMANCE_MODE");
    checkControl(handle, CAM_QHY5II_GUIDE_MODE, "CAM_QHY5II_GUIDE_MODE");
    checkControl(handle, DDR_BUFFER_CAPACITY, "DDR_BUFFER_CAPACITY");
    checkControl(handle, DDR_BUFFER_READ_THRESHOLD, "DDR_BUFFER_READ_THRESHOLD");
    checkControl(handle, DefaultGain, "DefaultGain");
    checkControl(handle, DefaultOffset, "DefaultOffset");
    checkControl(handle, OutputDataActualBits, "OutputDataActualBits");
    checkControl(handle, OutputDataAlignment, "OutputDataAlignment");
    checkControl(handle, CAM_SINGLEFRAMEMODE, "CAM_SINGLEFRAMEMODE");
    checkControl(handle, CAM_LIVEVIDEOMODE, "CAM_LIVEVIDEOMODE");
    checkControl(handle, CAM_IS_COLOR, "CAM_IS_COLOR");
    checkControl(handle, hasHardwareFrameCounter, "hasHardwareFrameCounter");
    checkControl(handle, CAM_HUMIDITY, "CAM_HUMIDITY");
    checkControl(handle, CAM_PRESSURE, "CAM_PRESSURE");
    checkControl(handle, CONTROL_VACUUM_PUMP, "CONTROL_VACUUM_PUMP");
    checkControl(handle, CONTROL_SensorChamberCycle_PUMP, "CONTROL_SensorChamberCycle_PUMP");
    checkControl(handle, CAM_32BITS, "CAM_32BITS");
    checkControl(handle, CAM_Sensor_ULVO_Status, "CAM_Sensor_ULVO_Status");
    checkControl(handle, CAM_SensorPhaseReTrain, "CAM_SensorPhaseReTrain");
    checkControl(handle, CAM_InitConfigFromFlash, "CAM_InitConfigFromFlash");
    checkControl(handle, CAM_TRIGER_MODE, "CAM_TRIGER_MODE");
    checkControl(handle, CAM_TRIGER_OUT, "CAM_TRIGER_OUT");
    checkControl(handle, CAM_BURST_MODE, "CAM_BURST_MODE");
    checkControl(handle, CAM_SPEAKER_LED_ALARM, "CAM_SPEAKER_LED_ALARM");
    checkControl(handle, CAM_WATCH_DOG_FPGA, "CAM_WATCH_DOG_FPGA");
    checkControl(handle, CAM_BIN6X6MODE, "CAM_BIN6X6MODE");
    checkControl(handle, CAM_BIN8X8MODE, "CAM_BIN8X8MODE");
    checkControl(handle, CAM_GlobalSensorGPSLED, "CAM_GlobalSensorGPSLED");
    checkControl(handle, CONTROL_ImgProc, "CONTROL_ImgProc");
    checkControl(handle, CONTROL_RemoveRBI, "CONTROL_RemoveRBI");
    checkControl(handle, CONTROL_AUTOWHITEBALANCE, "CONTROL_AUTOWHITEBALANCE");
    checkControl(handle, CONTROL_AUTOEXPOSURE, "CONTROL_AUTOEXPOSURE");
    checkControl(handle, CONTROL_ImageStabilization, "CONTROL_ImageStabilization");
    checkControl(handle, CONTROL_GlobalReset, "CONTROL_GlobalReset");
}

CameraStats getStats(qhyccd_handle* handle) {

    CameraStats stats;

    QHYRet ret;
    // Log useful information
    uint32_t numReadModes;
    ret = GetQHYCCDNumberOfReadModes(handle, &numReadModes);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to get read mode count.");
        throw std::runtime_error("Unable to get read mode count.");
    }
    spdlog::trace("Read mode count: {}", numReadModes);
    for (size_t i = 0; i < numReadModes; i++) {
        std::array<char, 256> readModeName;
        ret = GetQHYCCDReadModeName(handle, i, readModeName.data());
        if (ret != QHYCCD_SUCCESS) {
            spdlog::error("Unable to get read mode name.");
            throw std::runtime_error("Unable to get read mode name.");
        }
        spdlog::trace("\tRead Mode: {}", std::string(readModeName.data()));
        stats.readModes.push_back(std::string(readModeName.data()));
    }

    // Log useful information
    ret = GetQHYCCDChipInfo(
            handle,
            &stats.sensorSize.first,
            &stats.sensorSize.second,
            &stats.sensorArea.sizeX,
            &stats.sensorArea.sizeY,
            &stats.pixelSize.first,
            &stats.pixelSize.second,
            &stats.nativeBits);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to get chip info.");
        throw std::runtime_error("Unable to get chip info.");
    }
    stats.sensorArea.startX = 0;
    stats.sensorArea.startY = 0;

    ret = GetQHYCCDEffectiveArea(
            handle,
            &stats.effectiveArea.startX,
            &stats.effectiveArea.startY,
            &stats.effectiveArea.sizeX,
            &stats.effectiveArea.sizeY);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to get chip info.");
        throw std::runtime_error("Unable to get chip info.");
    }

    ret = GetQHYCCDOverScanArea(
            handle,
            &stats.overscanArea.startX,
            &stats.overscanArea.startY,
            &stats.overscanArea.sizeX,
            &stats.overscanArea.sizeY);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to get chip info.");
        throw std::runtime_error("Unable to get chip info.");
    }

    spdlog::trace("Sensor area: {}", stats.sensorArea);
    spdlog::trace("Effective area: {}", stats.effectiveArea);
    spdlog::trace("Overscan area: {}", stats.overscanArea);
    spdlog::trace("Sensor Size: {}x{}", stats.sensorSize.first, stats.sensorSize.second);
    spdlog::trace("Pixel Size: {}x{}", stats.pixelSize.first, stats.pixelSize.second);

    return stats;
}


Camera::Camera(char* const cameraID) : _cameraID(cameraID) {
    QHYRet ret;

    spdlog::debug("Starting Constructing camera with ID: {}.", _cameraID);

    _cameraHandle = OpenQHYCCD(cameraID);
    if (_cameraHandle == nullptr) {
        spdlog::error("Unable to open camera with ID: {}.", _cameraID);
        throw std::runtime_error("Unable to open camera.");
    }

    // Log useful information
    checkControls(_cameraHandle);
    _stats = getStats(_cameraHandle);

    // Read mode MUST be set before init
    ret = SetQHYCCDReadMode(_cameraHandle, 0);  // Photographic mode (for now)
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to set read mode.");
        throw std::runtime_error("Unable to set read mode.");
    }

    // Stream mode MUST be set before init
    ret = SetQHYCCDStreamMode(_cameraHandle, 0x01);  // 0x00 is single, 0x01 is live)
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to set streaming mode.");
        throw std::runtime_error("Unable to set streaming mode.");
    }

    // Now we can init
    ret = InitQHYCCD(_cameraHandle);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to initialize camera with ID: {}.", _cameraID);
        throw std::runtime_error("Unable to initialize camera.");
    }

    ret = SetQHYCCDBitsMode(_cameraHandle, 16);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to set bits mode.");
        throw std::runtime_error("Unable to set bits mode.");
    }

    // Initialize ROI to the full sensor
    setRoi(_stats.sensorArea);
    // setRoi({0, 0, 100, 100});

    _memLength = GetQHYCCDMemLength(_cameraHandle);
    spdlog::trace("Memory length: {}", _memLength);
    _framebuffer.resize(_memLength);

    ret = BeginQHYCCDLive(_cameraHandle);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to begin live stream.");
        throw std::runtime_error("Unable to begin live stream.");
    }
    spdlog::debug("Live mode enabled.");

    // TEST
    uint32_t liveWidth = 0;
    uint32_t liveHeight = 0;
    uint32_t liveBpp = 0;
    uint32_t liveChannels = 0;
    while (true) {
        bool gotFrame = false;
        spdlog::debug("Start Frame Acquire");
        while (true) {
            ret = GetQHYCCDLiveFrame(
                    _cameraHandle,
                    &liveWidth,
                    &liveHeight,
                    &liveBpp,
                    &liveChannels,
                    _framebuffer.data());
            if (ret == QHYCCD_SUCCESS) {
                gotFrame = true;
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        spdlog::debug("End Frame Acquire");
        spdlog::debug("{} {} {} {}", liveWidth, liveHeight, liveBpp, liveChannels);
    }
    // TEST

    _startStream();

    spdlog::debug("Finished Constructing camera with ID: {}.", _cameraID);
}


Camera::~Camera() {
    if (_cameraHandle != nullptr) {
        spdlog::debug("Starting Destructing camera with ID: {}.", _cameraID);

        _shouldStream = false;
        if (_frameStreamThread.joinable()) {
            _frameStreamThread.join();
        }

        QHYRet ret = StopQHYCCDLive(_cameraHandle);
        if (ret != QHYCCD_SUCCESS) {
            spdlog::error("Unable to stop live stream.");
            // Welp.
        }
        spdlog::debug("Live mode disabled.");

        _filterMoving = false;
        if (_filterMovingThread.joinable()) {
            _filterMovingThread.join();
        }
        _temperatureControlActive = false;
        if (_temperatureControlThread.joinable()) {
            _temperatureControlThread.join();
        }

        ret = CloseQHYCCD(_cameraHandle);
        if (ret != QHYCCD_SUCCESS) {
            spdlog::error("Unable to close camera with ID: {}.", _cameraID);
            // Welp.
        }
        spdlog::debug("Finished Destructing camera with ID: {}.", _cameraID);
    }
}


void Camera::setGain(size_t gain) {
    _gain = static_cast<double>(gain);
    spdlog::debug("Setting gain to {}", _gain);

    // TODO bounds check
    QHYRet ret = SetQHYCCDParam(_cameraHandle, CONTROL_GAIN, _gain);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to set gain to {}.", _gain);
        throw std::runtime_error("Unable to set gain.");
    }
}


void Camera::setOffset(size_t offset) {
    _offset = static_cast<double>(offset);
    spdlog::debug("Setting offset to {}", _offset);

    // TODO bounds check
    QHYRet ret = SetQHYCCDParam(_cameraHandle, CONTROL_OFFSET, _offset);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to set offset to {}.", _offset);
        throw std::runtime_error("Unable to set offset.");
    }
}


void Camera::setExposure(size_t exposure) {
    _exposure = static_cast<double>(exposure);
    spdlog::debug("Setting exposure to {}", _exposure);

    // TODO bounds check
    QHYRet ret = SetQHYCCDParam(_cameraHandle, CONTROL_EXPOSURE, _exposure);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to set exposure to {}.", _exposure);
        throw std::runtime_error("Unable to set exposure.");
    }
}

void Camera::setBinMode(BinMode mode) {
    _binMode = mode;

    uint32_t bin = 0;
    switch (_binMode) {
    case BinMode::BIN_1x1:
        bin = 1;
        break;
    case BinMode::BIN_2x2:
        bin = 2;
        break;
    case BinMode::BIN_3x3:
        bin = 3;
        break;
    case BinMode::BIN_4x4:
        bin = 4;
        break;
    default:
        throw std::runtime_error("Unknown binning mode.");
        break;
    }
    QHYRet ret = SetQHYCCDBinMode(_cameraHandle, bin, bin);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to set bin mode to {}x{}.", bin, bin);
        throw std::runtime_error("Unable to set bin mode.");
    }
}


void Camera::setRoi(const Roi& roi) {
    QHYRet ret = SetQHYCCDResolution(_cameraHandle, roi.startX, roi.startY, roi.sizeX, roi.sizeY);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to set resolution: {}.", roi);
        throw std::runtime_error("Unable to set resolution.");
    }
    _roi = roi;
}


void Camera::setFilterWheelPosition(size_t position) {
    if (_filterMoving) {
        spdlog::warn("Filter wheel already in motion; ignoring new position.");
        return;
    }

    // Clear out a previous thread, if existing
    if (_filterMovingThread.joinable()) {
        _filterMovingThread.join();
    }

    // Check that the wheel is there
    if (IsQHYCCDCFWPlugged(_cameraHandle) != QHYCCD_SUCCESS) {
        spdlog::error("Unable to contact filter wheel.");
        throw std::runtime_error("Unable to contact filter wheel.");
    }

    _filterMoving = true;
    _filterPosition = position;
    spdlog::debug("Setting filter wheel to position {}", _filterPosition);

    std::string order = std::to_string(position);
    QHYRet ret = SendOrder2QHYCCDCFW(_cameraHandle, const_cast<char*>(order.c_str()), order.size());
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to send order to filter wheel.");
        throw std::runtime_error("Unable to send order to filter wheel.");
    }

    _filterMovingThread = std::thread([&, order]() {
        char buffer[4];
        while (true) {
            memset(buffer, 0, 4);
            GetQHYCCDCFWStatus(_cameraHandle, buffer);
            spdlog::trace("filter wheel: (current: {}, target:{})", buffer, order);
            if (!strncmp(order.c_str(), buffer, order.size())) {
                break;
            }
        }
        spdlog::debug("Filter wheel move complete: {}", _filterPosition);
        _filterMoving = false;
    });
}


void Camera::waitFilterWheel() {
    while (_filterMoving) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}


void Camera::startTemperatureControl(double targetTemperature) {
    _targetTemperature = targetTemperature;
    spdlog::debug("Starting temperature control: {}", _targetTemperature);

    stopTemperatureControl();
    _temperatureControlActive = true;

    _temperatureControlThread = std::thread([&]() {
        while (_temperatureControlActive) {
            ControlQHYCCDTemp(_cameraHandle, _targetTemperature);
            std::this_thread::sleep_for(std::chrono::milliseconds(900));
        }
    });
}


void Camera::stopTemperatureControl() {
    _temperatureControlActive = false;
    if (_temperatureControlThread.joinable()) {
        _temperatureControlThread.join();
    }
}


bool Camera::isTemperatureStabilized(double threshold) {
    double currentTemperature = GetQHYCCDParam(_cameraHandle, CONTROL_CURTEMP);
    if (std::abs(currentTemperature - _targetTemperature) <= threshold) {
        return true;
    } else {
        return false;
    }
}


const std::string& Camera::getCameraID() {
    return _cameraID;
}


double Camera::getTemperature() {
    double temperature = GetQHYCCDParam(_cameraHandle, CONTROL_CURTEMP);
    return temperature;
}

double Camera::getTecPwm() {
    double pwm = GetQHYCCDParam(_cameraHandle, CONTROL_CURPWM);
    return pwm;
}

Roi Camera::getRoi() {
    Roi roi;
    QHYRet ret =
            GetQHYCCDCurrentROI(_cameraHandle, &roi.startX, &roi.startY, &roi.sizeX, &roi.sizeY);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to get current ROI.");
        throw std::runtime_error("Unable to get current ROI.");
    }
    return roi;
}


void Camera::exposeSingle() {
    QHYRet ret;

    spdlog::trace("Start exposure.");
    ret = ExpQHYCCDSingleFrame(_cameraHandle);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to start exposure.");
    }

    uint32_t remainingTEMP = GetQHYCCDExposureRemaining(_cameraHandle);
    spdlog::trace("Remaining:{}", remainingTEMP);

    uint32_t width;
    uint32_t height;
    uint32_t bpp;
    uint32_t channels;

    spdlog::trace("{}, {}", (void*)_framebuffer.data(), _framebuffer.size());

    GetQHYCCDSingleFrame(_cameraHandle, &width, &height, &bpp, &channels, _framebuffer.data());
    spdlog::trace("width:{}, height:{}, bpp:{}, channels:{}", width, height, bpp, channels);
    spdlog::trace("End exposure.");
}


void Camera::writeBuffer(const std::string& filepath) {

    const int color_type = PNG_COLOR_TYPE_GRAY;

    // Open the file for writing
    FILE* fp = fopen(filepath.c_str(), "wb");
    if (!fp) {
        spdlog::error("Failed to open file {}", filepath);
        return;
    }

    // Create the PNG write struct
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        spdlog::error("Failed to create PNG write struct.");
        fclose(fp);
        return;
    }

    // Create the PNG info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        spdlog::error("Failed to create PNG info struct.");
        png_destroy_write_struct(&png_ptr, NULL);
        fclose(fp);
        return;
    }

    // Set error handling
    if (setjmp(png_jmpbuf(png_ptr))) {
        spdlog::error("An error occurred while writing the PNG file.");
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return;
    }

    // Set up the PNG write
    png_init_io(png_ptr, fp);
    png_set_IHDR(
            png_ptr,
            info_ptr,
            _roi.sizeX,
            _roi.sizeY,
            16,
            color_type,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT);

    // Write the PNG header
    png_write_info(png_ptr, info_ptr);


    std::vector<uint8_t> data;
    data.resize(2 * _roi.sizeX * _roi.sizeY);
    for (size_t i = 0; i < _roi.sizeX * _roi.sizeY; i++) {
        uint16_t value = (static_cast<uint16_t>(_framebuffer[2 * i]) << 0)
                         | (static_cast<uint16_t>(_framebuffer[2 * i + 1]) << 8);
        float valueF = static_cast<float>(value) / 65535;
        valueF = std::sqrt(valueF);
        value = static_cast<uint16_t>(valueF * 65535);
        data[2 * i + 1] = (value & 0x00ff);
        data[2 * i] = (value & 0xff00) >> 8;
    }

    for (size_t y = 0; y < _roi.sizeY; y++) {
        png_bytep row = reinterpret_cast<png_bytep>(data.data() + y * (2 * _roi.sizeX));
        png_write_row(png_ptr, row);
    }

    // End the PNG write
    png_write_end(png_ptr, info_ptr);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

    spdlog::trace("PNG written.");
}

void Camera::thingy() {

    uint32_t width = _roi.sizeX;
    uint32_t height = _roi.sizeY;
    uint32_t bpp = 16;
    uint32_t channels = 1;
    while (true) {
        QHYRet ret = GetQHYCCDLiveFrame(
                _cameraHandle, &width, &height, &bpp, &channels, _framebuffer.data());
        if (ret != QHYCCD_SUCCESS) {
            spdlog::error("Unable to get live frame: error {}.", ret);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            //  throw std::runtime_error("Unable to get live frame.");
        }
        spdlog::trace("frame: {} {} {} {}", width, height, bpp, channels);
    }
}


void Camera::registerFrameCallback(FrameCallback callback) {
    _frameCallback = callback;
}


void Camera::_startStream() {

    _frameStreamThread = std::thread([&]() {
        uint32_t width;
        uint32_t height;
        uint32_t bpp;
        uint32_t channels;
        std::vector<uint8_t> framebuffer;
        framebuffer.resize(_memLength);
        while (_shouldStream) {
            QHYRet ret = GetQHYCCDLiveFrame(
                    _cameraHandle, &width, &height, &bpp, &channels, framebuffer.data());
            if (ret == QHYCCD_SUCCESS) {
                spdlog::trace("Got frame: {} {} {} {}", width, height, bpp, channels);
                if (_frameCallback != nullptr) {
                    _frameCallback({});  // TODO: Make frame
                }
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    });
}
