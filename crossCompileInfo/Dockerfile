FROM ubuntu:20.04

# Avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies and cross-compilation tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    wget \
    python3 \
    pkg-config \
    libfontconfig1-dev \
    libfreetype6-dev \
    libx11-dev \
    libx11-xcb-dev \
    libxext-dev \
    libxfixes-dev \
    libxi-dev \
    libxrender-dev \
    libxcb1-dev \
    libxcb-glx0-dev \
    libxcb-keysyms1-dev \
    libxcb-image0-dev \
    libxcb-shm0-dev \
    libxcb-icccm4-dev \
    libxcb-sync-dev \
    libxcb-xfixes0-dev \
    libxcb-shape0-dev \
    libxcb-randr0-dev \
    libxcb-render-util0-dev \
    libxkbcommon-dev \
    libxkbcommon-x11-dev \
    libglib2.0-dev \
    libsqlite3-dev \
    libpq-dev \
    libmysqlclient-dev \
    libssl-dev \
    libgles2-mesa-dev \
    libegl1-mesa-dev \
    libgbm-dev \
    libdrm-dev \
    libinput-dev \
    libudev-dev \
    libts-dev \
    libasound2-dev \
    crossbuild-essential-armhf \
    gcc-arm-linux-gnueabihf \
    g++-arm-linux-gnueabihf \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set up working directory
WORKDIR /opt

# Download Raspberry Pi tools
RUN git clone --depth=1 https://github.com/raspberrypi/tools.git rpi-tools

# Add toolchain to PATH
ENV PATH="/opt/rpi-tools/arm-bcm2708/arm-linux-gnueabihf/bin:${PATH}"

# Download Qt source code (Qt 6.3.2)
RUN wget https://download.qt.io/archive/qt/6.3/6.3.2/single/qt-everywhere-src-6.3.2.tar.xz \
    && tar xf qt-everywhere-src-6.3.2.tar.xz \
    && rm qt-everywhere-src-6.3.2.tar.xz

# Create a directory for build artifacts
RUN mkdir -p /opt/qt6pi

# Download and prepare a basic cross-compilation toolchain file
RUN mkdir -p /opt/qt-build
WORKDIR /opt
RUN echo 'set(CMAKE_SYSTEM_NAME Linux)\n\
set(CMAKE_SYSTEM_PROCESSOR arm)\n\
\n\
set(TARGET_SYSROOT /opt/sysroot)\n\
set(CROSS_COMPILER /usr/bin/arm-linux-gnueabihf)\n\
\n\
# specify the cross compiler\n\
set(CMAKE_C_COMPILER ${CROSS_COMPILER}-gcc)\n\
set(CMAKE_CXX_COMPILER ${CROSS_COMPILER}-g++)\n\
\n\
# where is the target environment\n\
set(CMAKE_SYSROOT ${TARGET_SYSROOT})\n\
set(CMAKE_FIND_ROOT_PATH ${TARGET_SYSROOT})\n\
\n\
# search for programs in the build host directories\n\
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)\n\
# search for libraries and headers in the target directories\n\
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)\n\
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)\n\
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)\n\
\n\
# Make sure Qt can find EGL and OpenGL ES 2.0\n\
set(OpenGL_GL_PREFERENCE GLVND)\n\
set(OPENGL_egl_LIBRARY ${TARGET_SYSROOT}/usr/lib/arm-linux-gnueabihf/libEGL.so)\n\
set(OPENGL_gles2_LIBRARY ${TARGET_SYSROOT}/usr/lib/arm-linux-gnueabihf/libGLESv2.so)\n' > /opt/rpi-toolchain.cmake

# Create the cross-compilation build script
RUN echo '#!/bin/bash\n\
\n\
# Set the target platform\n\
RASPI_TOOLCHAIN=/opt/rpi-tools/arm-bcm2708/arm-linux-gnueabihf\n\
RASPI_SYSROOT=/opt/sysroot\n\
\n\
# Configure Qt 6 for Raspberry Pi using CMake\n\
cd /opt/qt-build\n\
\n\
# Configure with CMake\n\
cmake -G Ninja \\\n\
      -DCMAKE_TOOLCHAIN_FILE=/opt/rpi-toolchain.cmake \\\n\
      -DQT_HOST_PATH=/opt/qt6-host \\\n\
      -DCMAKE_PREFIX_PATH=/opt/qt6-host \\\n\
      -DCMAKE_BUILD_TYPE=Release \\\n\
      -DCMAKE_INSTALL_PREFIX=/usr/local/qt6pi \\\n\
      -DQT_BUILD_EXAMPLES=OFF \\\n\
      -DQT_BUILD_TESTS=OFF \\\n\
      -DFEATURE_xcb=ON \\\n\
      -DFEATURE_eglfs=ON \\\n\
      -DFEATURE_opengl_dynamic=ON \\\n\
      -DFEATURE_sql=ON \\\n\
      -DFEATURE_sql_sqlite=ON \\\n\
      -DFEATURE_sql_mysql=ON \\\n\
      -DFEATURE_sql_psql=ON \\\n\
      -DFEATURE_system_sqlite=ON \\\n\
      -DFEATURE_geoservices=ON \\\n\
      -DFEATURE_location=ON \\\n\
      -DINPUT_openssl=linked \\\n\
      -DINPUT_xcb=yes \\\n\
      -DINPUT_eglfs=yes \\\n\
      ../qt-everywhere-src-6.3.2\n\
\n\
# Build Qt\n\
cmake --build . --parallel $(nproc)\n\
\n\
# Install Qt\n\
cmake --install . --prefix=/opt/qt6pi\n' > /opt/build-qt6.sh

# Create a script to first build Qt for the host system
RUN echo '#!/bin/bash\n\
\n\
# Set up host build of Qt first (needed for cross-compilation)\n\
mkdir -p /opt/qt6-host-build\n\
cd /opt/qt6-host-build\n\
\n\
# Configure Qt for the host\n\
cmake -G Ninja \\\n\
      -DCMAKE_BUILD_TYPE=Release \\\n\
      -DCMAKE_INSTALL_PREFIX=/opt/qt6-host \\\n\
      -DQT_BUILD_EXAMPLES=OFF \\\n\
      -DQT_BUILD_TESTS=OFF \\\n\
      ../qt-everywhere-src-6.3.2\n\
\n\
# Build and install host Qt\n\
cmake --build . --parallel $(nproc)\n\
cmake --install .\n' > /opt/build-qt6-host.sh

# Make the build scripts executable
RUN chmod +x /opt/build-qt6.sh
RUN chmod +x /opt/build-qt6-host.sh

# Create mock sysroot directory structure for the target
COPY sysroot /opt/

# Create a test script for compiler functionality
RUN echo '#!/bin/bash\n\
\n\
# Test if the cross compiler works\n\
echo "#include <stdio.h>\nint main() { printf(\"Hello from Raspberry Pi\\n\"); return 0; }" > test.c\n\
arm-linux-gnueabihf-gcc -o test test.c\n\
file test\n' > /opt/test-compiler.sh

# Make the scripts executable
RUN chmod +x /opt/test-compiler.sh
RUN chmod +x /opt/setup-sysroot.sh

# Set up the entrypoint for interactive use
WORKDIR /opt
CMD ["/bin/bash"]