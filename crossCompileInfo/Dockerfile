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
    nano \
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

COPY sysroot /opt/sysroot

COPY toolchainQt.cmake /opt/toolchainQt.cmake

# Download Qt source code (Qt 6.3.2)
RUN wget https://download.qt.io/archive/qt/6.3/6.3.2/submodules/qtbase-everywhere-src-6.3.2.tar.xz \
    && tar -xf qtbase-everywhere-src-6.3.2.tar.xz \
    && rm qtbase-everywhere-src-6.3.2.tar.xz

RUN wget https://download.qt.io/archive/qt/6.3/6.3.2/submodules/qtdeclarative-everywhere-src-6.3.2.tar.xz \
    && tar -xf qtdeclarative-everywhere-src-6.3.2.tar.xz \
    && rm qtdeclarative-everywhere-src-6.3.2.tar.xz

RUN wget https://download.qt.io/archive/qt/6.3/6.3.2/submodules/qtshadertools-everywhere-src-6.3.2.tar.xz \
    && tar -xf qtshadertools-everywhere-src-6.3.2.tar.xz \
    && rm qtshadertools-everywhere-src-6.3.2.tar.xz

RUN wget https://download.qt.io/archive/qt/6.3/6.3.2/submodules/qtsvg-everywhere-src-6.3.2.tar.xz \
    && tar -xf qtsvg-everywhere-src-6.3.2.tar.xz \
    && rm qtsvg-everywhere-src-6.3.2.tar.xz


RUN git clone https://code.qt.io/qt/qtpositioning.git

RUN git clone https://code.qt.io/qt/qtlocation.git

# Create a directory for build artifacts
RUN mkdir -p /opt/qt6pi

# Download and prepare a basic cross-compilation toolchain file
RUN mkdir -p /opt/qt-build
WORKDIR /opt

# Create the cross-compilation build script
RUN echo '#!/bin/bash\n\
\n\
RASPI_SYSROOT=/opt/sysroot\n\
\n\
# Configure Qt 6 for Raspberry Pi using CMake\n\
cd /opt/qt-build\n\
\n\
# Configure with CMake\n\
cmake -GNinja \\\n\
      -DCMAKE_TOOLCHAIN_FILE=/opt/toolchainQt.cmake \\\n\
      -DQT_HOST_PATH=/opt/qt6-host \\\n\
      -DCMAKE_PREFIX_PATH=/opt/qt6-host \\\n\
      -DFEATURE_translations=OFF \\\n\
      -DCMAKE_BUILD_TYPE=Release \\\n\
      -DCMAKE_INSTALL_PREFIX=/opt/qt6pi \\\n\
      -DQT_BUILD_EXAMPLES=OFF \\\n\
      -DQT_BUILD_TESTS=OFF \\\n\
      -DQT_FEATURE_eglfs_egldevice=ON \\\n\
      -DQT_FEATURE_eglfs_gbm=ON \\\n\
      -DQT_BUILD_TOOLS_WHEN_CROSSCOMPILING=ON \\\n\
      -DPKG_CONFIG_SYSROOT_DIR=/opt/sysroot \\n\
      -DQT_FEATURE_opengl_desktop=OFF \
    -DQT_FEATURE_egl=ON \\\n\
      -DFEATURE_xkbcommon_x11=ON \\n\
      -DFEATURE_sql=ON \\\n\
      -DFEATURE_sql_sqlite=ON \\\n\
      -DFEATURE_sql_psql=ON \\\n\
      -DFEATURE_system_sqlite=ON \\\n\
      ../qtbase-everywhere-src-6.3.2\n\
\n\
# Build Qt\n\
cmake --build . --parallel $(nproc)\n\
\n\
# Install Qt\n\
cmake --install . --prefix=/opt/qt6pi' > /opt/build-qt6.sh

# Create a script to first build Qt for the host system
RUN mkdir -p /opt/qt6-host-build \
 && cd /opt/qt6-host-build \
 && cmake -GNinja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/opt/qt6-host \
      -DFEATURE_translations=OFF \
      -DQT_BUILD_EXAMPLES=OFF \
      -DQT_BUILD_TESTS=OFF \
      ../qtbase-everywhere-src-6.3.2 \
 && cmake --build . --parallel 4 \
 && cmake --install . 

 RUN cd /opt/qtshadertools-everywhere-src-6.3.2 \
 && mkdir build \
 && cd build \
 && /opt/qt6-host/bin/qt-cmake -GNinja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/opt/qt6-host \
      -DFEATURE_translations=OFF \
      -DQT_BUILD_EXAMPLES=OFF \
      -DQT_BUILD_TESTS=OFF \
      .. \
 && cmake --build . --parallel 4 \
 && cmake --install .
 
 RUN cd /opt/qtdeclarative-everywhere-src-6.3.2 \
 && mkdir build \
 && cd build \
 && /opt/qt6-host/bin/qt-cmake -GNinja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/opt/qt6-host \
      -DFEATURE_translations=OFF \
      -DQT_BUILD_EXAMPLES=OFF \
      -DQT_BUILD_TESTS=OFF \
      .. \
 && cmake --build . --parallel 4 \
 && cmake --install .

RUN cd /opt/qtpositioning \
 && mkdir build \
 && cd build \
 && /opt/qt6-host/bin/qt-cmake -GNinja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/opt/qt6-host \
      -DFEATURE_translations=OFF \
      -DQT_BUILD_EXAMPLES=OFF \
      -DQT_BUILD_TESTS=OFF \
      .. \
 && cmake --build . --parallel 4 \
 && cmake --install .


RUN cd /opt/qtlocation \
 && mkdir build \
 && cd build \
 && /opt/qt6-host/bin/qt-cmake -GNinja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/opt/qt6-host \
      -DFEATURE_translations=OFF \
      -DQT_BUILD_EXAMPLES=OFF \
      -DQT_BUILD_TESTS=OFF \
      .. \
 && cmake --build . --parallel 4 \
 && cmake --install .

# Make the build scripts executable
RUN chmod +x /opt/build-qt6.sh

# Start build qt6pi
RUN /opt/build-qt6.sh

# Build shadertools for pi
RUN cd /opt/qtshadertools-everywhere-src-6.3.2 \
    && rm -r build \
    && mkdir build \
    && cd build \
    /opt/qt6pi/bin/qt-cmake -GNinja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/opt/qt6pi \
    -DFEATURE_translations=OFF \
    -DQT_BUILD_EXAMPLES=OFF \
    -DQT_BUILD_TESTS=OFF \
    .. \
&& cmake --build . --parallel 4 \
&& cmake --install .

# Build declarative for pi
RUN cd /opt/qtdeclarative-everywhere-src-6.3.2 \
    && rm -r build \
    && mkdir build \
    && cd build \
    /opt/qt6pi/bin/qt-cmake -GNinja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/opt/qt6pi \
    -DFEATURE_translations=OFF \
    -DQT_BUILD_EXAMPLES=OFF \
    -DQT_BUILD_TESTS=OFF \
    .. \
&& cmake --build . --parallel 4 \
&& cmake --install .

# Build declarative for pi
RUN cd /opt/qtdeclarative-everywhere-src-6.3.2 \
    && rm -r build \
    && mkdir build \
    && cd build \
    /opt/qt6pi/bin/qt-cmake -GNinja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/opt/qt6pi \
    -DFEATURE_translations=OFF \
    -DQT_BUILD_EXAMPLES=OFF \
    -DQT_BUILD_TESTS=OFF \
    .. \
&& cmake --build . --parallel 4 \
&& cmake --install .

RUN cd /opt/qtpositioning \
 && mkdir build \
 && cd build \
 && /opt/qt6pi/bin/qt-cmake -GNinja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/opt/qt6pi \
      -DFEATURE_translations=OFF \
      -DQT_BUILD_EXAMPLES=OFF \
      -DQT_BUILD_TESTS=OFF \
      .. \
 && cmake --build . --parallel 4 \
 && cmake --install .


RUN cd /opt/qtlocation \
 && mkdir build \
 && cd build \
 && /opt/qt6pi/bin/qt-cmake -GNinja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/opt/qt6pi \
      -DFEATURE_translations=OFF \
      -DQT_BUILD_EXAMPLES=OFF \
      -DQT_BUILD_TESTS=OFF \
      .. \
 && cmake --build . --parallel 4 \
 && cmake --install .

# Create a test script for compiler functionality
RUN echo '#!/bin/bash\n\
\n\
# Test if the cross compiler works\n\
echo "#include <stdio.h>\nint main() { printf(\"Hello from Raspberry Pi\\n\"); return 0; }" > test.c\n\
arm-linux-gnueabihf-gcc -o test test.c\n\
file test\n' > /opt/test-compiler.sh

# Make the scripts executable
RUN chmod +x /opt/test-compiler.sh

# Set up the entrypoint for interactive use
WORKDIR /opt
CMD ["/bin/bash"]