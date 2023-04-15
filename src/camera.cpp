#include "camera.hpp"

#include "qhy.hpp"
#include "spdlog/spdlog.h"

#include <chrono>
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


Camera::Camera(char* const cameraID) : _cameraID(cameraID) {
    QHYRet ret;

    spdlog::trace("Constructing camera with ID {}.", _cameraID);

    _cameraHandle = OpenQHYCCD(cameraID);
    if (_cameraHandle == nullptr) {
        spdlog::error("Unable to open camera with ID {}.", _cameraID);
        throw std::runtime_error("Unable to open camera.");
    }

    ret = InitQHYCCD(_cameraHandle);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to initialize camera with ID {}.", _cameraID);
        throw std::runtime_error("Unable to initialize camera.");
    }

    checkControls(_cameraHandle);

    ret = SetQHYCCDStreamMode(_cameraHandle, 0x00);  // 0x00 is single, 0x01 is live)
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to set streaming mode.");
        throw std::runtime_error("Unable to set streaming mode.");
    }

    uint32_t memLength = GetQHYCCDMemLength(_cameraHandle);
    spdlog::debug("Memory length: {}", memLength);
    _framebuffer.resize(memLength);


    SetQHYCCDBitsMode(_cameraHandle, 16);

    SetQHYCCDResolution(_cameraHandle, 0, 0, 8000, 5000);

    ret = IsQHYCCDCFWPlugged(_cameraHandle);
    spdlog::debug("Filter wheel attached: {}", ret == QHYCCD_SUCCESS ? "yes" : "no");
}

Camera::~Camera() {
    spdlog::trace("Destructing camera with ID {}.", _cameraID);
    if (_cameraHandle != nullptr) {
        QHYRet ret = CloseQHYCCD(_cameraHandle);
        if (ret != QHYCCD_SUCCESS) {
            spdlog::error("Unable to close camera with ID {}.", _cameraID);
            // Welp.
        }
    }
}

void Camera::setExposureUs(size_t us) {
    QHYRet ret;

    // TODO bounds check
    ret = SetQHYCCDParam(_cameraHandle, CONTROL_EXPOSURE, (double)us);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to set exposure to {}.", us);
        throw std::runtime_error("Unable to set exposure.");
    }
}


void Camera::doThing() {
    QHYRet ret;

    spdlog::trace("Start exposure.");
    ret = ExpQHYCCDSingleFrame(_cameraHandle);
    if (ret != QHYCCD_SUCCESS) {
        spdlog::error("Unable to start exposure.");
    }

    uint32_t width;
    uint32_t height;
    uint32_t bpp;
    uint32_t channels;

    spdlog::trace("{}, {}", (void*)_framebuffer.data(), _framebuffer.size());

    GetQHYCCDSingleFrame(_cameraHandle, &width, &height, &bpp, &channels, _framebuffer.data());
    spdlog::trace("width:{}, height:{}, bpp:{}, channels:{}", width, height, bpp, channels);
    spdlog::trace("End exposure.");
}


void Camera::doOtherThing() {

    SetQHYCCDStreamMode(_cameraHandle, 0x01);
    BeginQHYCCDLive(_cameraHandle);
    uint32_t width;
    uint32_t height;
    uint32_t bpp;
    uint32_t channels;

    for (size_t i = 0; i < 20; i++) {
        spdlog::trace("{}, {}", (void*)_framebuffer.data(), _framebuffer.size());

        GetQHYCCDLiveFrame(_cameraHandle, &width, &height, &bpp, &channels, _framebuffer.data());
    }

    StopQHYCCDLive(_cameraHandle);
}

void Camera::temperatureThing() {

    // SetQHYCCDParam(_cameraHandle, CONTROL_MANULPWM, 255);

    while (true) {
        ControlQHYCCDTemp(_cameraHandle, 0.0);
        double pwm = GetQHYCCDParam(_cameraHandle, CONTROL_CURPWM);
        double temp = GetQHYCCDParam(_cameraHandle, CONTROL_CURTEMP);
        spdlog::debug("{}\t{}", temp, pwm);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    while (true) {

        double pwm = GetQHYCCDParam(_cameraHandle, CONTROL_CURPWM);
        double temp = GetQHYCCDParam(_cameraHandle, CONTROL_CURTEMP);
        spdlog::debug("{}\t{}", temp, pwm);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
