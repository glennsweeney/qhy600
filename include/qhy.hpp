#pragma once

#include "camera.hpp"

#include <cstdint>

using QHYRet = uint32_t;

constexpr size_t QHY_ID_BUFFER_LEN = 256;
using CameraId = std::array<char, QHY_ID_BUFFER_LEN>;


void init();
void deinit();

std::vector<CameraId> scanCameras();
