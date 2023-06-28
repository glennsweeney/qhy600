
#include "qhy.hpp"
#include "qhyccd.h"

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

namespace {

TEST(QHY, QHY_LIVE_MODE) {

    spdlog::set_level(spdlog::level::trace);

    // Initialize the library
    QHYRet ret = InitQHYCCDResource();
    ASSERT_EQ(ret, QHYCCD_SUCCESS);

    // Identify cameras
    uint32_t cameraCount = ScanQHYCCD();
    ASSERT_EQ(cameraCount, 1);

    // Get camera ID
    char cameraID[256];
    ret = GetQHYCCDId(0, cameraID);
    ASSERT_EQ(ret, QHYCCD_SUCCESS);


    qhyccd_handle* camera = OpenQHYCCD(cameraID);
    ASSERT_NE(camera, nullptr);

    ret = SetQHYCCDReadMode(camera, 0);  // Photographic mode = 0
    ASSERT_EQ(ret, QHYCCD_SUCCESS);

    ret = SetQHYCCDStreamMode(camera, 0x01);  // 0x00 is single, 0x01 is live)
    ASSERT_EQ(ret, QHYCCD_SUCCESS);

    ret = InitQHYCCD(camera);
    ASSERT_EQ(ret, QHYCCD_SUCCESS);

    ret = SetQHYCCDBitsMode(camera, 16);
    ASSERT_EQ(ret, QHYCCD_SUCCESS);

    uint32_t width = 9600;
    uint32_t height = 6422;
    // uint32_t width = 100;
    // uint32_t height = 100;
    ret = SetQHYCCDResolution(camera, 0, 0, width, height);
    ASSERT_EQ(ret, QHYCCD_SUCCESS);


    uint32_t memLength = GetQHYCCDMemLength(camera);
    ASSERT_GT(memLength, 0);
    std::vector<uint8_t> framebuffer(memLength);


    ret = BeginQHYCCDLive(camera);
    ASSERT_EQ(ret, QHYCCD_SUCCESS);

    uint32_t liveWidth = 0;
    uint32_t liveHeight = 0;
    uint32_t liveBpp = 0;
    uint32_t liveChannels = 0;

    while (true) {
        bool gotFrame = false;
        spdlog::debug("Start Frame Acquire");
        while (true) {
            ret = GetQHYCCDLiveFrame(
                    camera, &liveWidth, &liveHeight, &liveBpp, &liveChannels, framebuffer.data());
            if (ret == QHYCCD_SUCCESS) {
                gotFrame = true;
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        spdlog::debug("End Frame Acquire");
        spdlog::debug("{} {} {} {}", liveWidth, liveHeight, liveBpp, liveChannels);
        ASSERT_TRUE(gotFrame);
    }

    ret = StopQHYCCDLive(camera);
    ASSERT_EQ(ret, QHYCCD_SUCCESS);

    ret = CloseQHYCCD(camera);
    ASSERT_EQ(ret, QHYCCD_SUCCESS);

    ret = ReleaseQHYCCDResource();
    ASSERT_EQ(ret, QHYCCD_SUCCESS);
}

}  // namespace
