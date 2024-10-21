
FROM ubuntu:20.04


WORKDIR /qt

RUN apt-get update && apt-get install -y software-properties-common \
    && add-apt-repository universe \
    && add-apt-repository multiverse \
    && apt-get update

# RUN apt-get update && apt-get install -y \
#     build-essential \
#     git \
#     cmake \
#     gcc-arm-linux-gnueabihf \
#     g++-arm-linux-gnueabihf \
#     libgcc-10-dev-arm-linux-gnueabihf \
#     libstdc++-10-dev-arm-linux-gnueabihf \
#     libxcb-dev \
#     libegl1-mesa-dev \
#     libgles2-mesa-dev
RUN apt-get install -y \
    build-essential \
    git \
    cmake \
    gcc-arm-linux-gnueabihf \
    g++-arm-linux-gnueabihf \
    libgcc-10-dev-armel-cross \
    libstdc++-10-dev-armel-cross \
    libxcb1-dev \
    libegl1-mesa-dev \
    libgles2-mesa-dev

    RUN git clone https://code.qt.io/qt/qtbase.git && \
    cd qtbase && \
    git checkout 6.3.2 && \
    mkdir build && \
    cd build

# Configure and build QtBase for Raspberry Pi 3B
RUN cmake -DCMAKE_TOOLCHAIN_FILE=/sysroot/usr/share/qt6/mkspecs/linux-arm-gnueabihf-g++/qmake.conf -DQT_BUILD_EXAMPLES=OFF -DQT_BUILD_TESTS=OFF -DQT_FEATURE_xcb=ON -DQT_FEATURE_eglfs=ON -DQT_FEATURE_declarative=ON .. && \
    make -j4 && \
    make install

# Download and extract the QtDeclarative source code
RUN git clone https://code.qt.io/qt/qtdeclarative.git && \
    cd qtdeclarative && \
    git checkout v6.3.2 && \
    mkdir build && \
    cd build

# Configure and build QtDeclarative for Raspberry Pi 3B
RUN cmake -DCMAKE_TOOLCHAIN_FILE=/sysroot/usr/share/qt6/mkspecs/linux-arm-gnueabihf-g++/qmake.conf .. && \
    make -j4 && \
    make install

# Create a sysroot directory and copy the necessary files
RUN mkdir /sysroot && \
    cp -r /usr/include /sysroot && \
    cp -r /usr/lib /sysroot && \
    cp -r /usr/lib/arm-linux-gnueabihf /sysroot

# Set the environment variables for cross-compilation
ENV PATH=/usr/local/qt6/bin:$PATH
ENV PKG_CONFIG_PATH=/usr/local/qt6/lib/pkgconfig
ENV LD_LIBRARY_PATH=/usr/local/qt6/lib

# Verify the QtBase installation
RUN /usr/local/qt6/bin/qmake -v