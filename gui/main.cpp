#include "application.hpp"

#include <spdlog/spdlog.h>

int main(int, char**) {

    spdlog::set_level(spdlog::level::trace);

    Application app;

    app.run();

    return 0;
}
