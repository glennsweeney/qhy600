# qhy600


## Setup

1. QHY SDK (from [here](https://www.qhyccd.com/html/prepub/log_en.html#!log_en.md))
    ```bash
    wget https://www.qhyccd.com/file/repository/publish/SDK/230412/sdk_linux64_23.04.12.tgz
    tar -xzvf sdk_linux64_23.04.12.tgz
    mv sdk_linux64_23.04.12 qhy_sdk
    rm sdk_linux64_23.04.12.tgz
    cd qhy_sdk
    sudo bash install.sh
    cd -
    ```

1. System Packages
    ```bash
    sudo apt install -y git clang clang-tidy
    sudo apt install -y python3-pip python3-venv
    sudo apt install -y xorg-dev libxkbcommon-dev
    ```

1. Python Environment
    ```bash
    python3 -m venv .venv
    source .venv/bin/activate
    pip install --upgrade pip
    pip install -r requirements.txt
    ```

1. Meson build and test:

    ```bash
    CC=clang CXX=clang++ meson setup -Ddebug=true -Doptimization=g -Db_sanitize=address,undefined -Db_lundef=false build .
    meson compile -C build
    meson test -C build
    ```

    Note: if you want a release build, replace setup with `CC=clang CXX=clang++ meson setup --reconfigure -Ddebug=false -Db_ndebug=true -Db_lto=true -Doptimization=3 build .`

    Note: Other sanitizers are available, including `thread`, `memory`, and `leak`, but cannot be specificed simultaneously with `address,undefined`
