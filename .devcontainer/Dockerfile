# Start with a base image containing the necessary tools
FROM ubuntu:latest

#Install the necceary packages
RUN apt-get update && apt-get install -y \
    cmake \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    git \
    make \
    python3 \
    g++ \
    && rm -rf /var/lib/apt/lists/*

# Clone the Raspberry Pi Pico SDK
RUN git clone https://github.com/raspberrypi/pico-sdk.git
RUN cd pico-sdk && git submodule update --init

# Set the PICO_SDK_PATH environment variable
ENV PICO_SDK_PATH=/pico-sdk

#create a new directory for the build
RUN mkdir /build

# Set the working directory
WORKDIR /build
