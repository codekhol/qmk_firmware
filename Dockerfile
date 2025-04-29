FROM ubuntu:latest

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
    git \
    gcc \
    make \
    dfu-util \
    python3 \
    python3-pip \
    python3-setuptools \
    curl \
    libsdl2-dev \
    libudev-dev \
    libusb-1.0-0-dev \
    gcc-arm-none-eabi \
    binutils-arm-none-eabi \
    && apt-get clean

# Debugging: Check if curl and python3 are available
RUN curl --version && python3 --version

# Test basic Python command
RUN python3 -c "print('Python3 is working!')"

# Test basic curl download
RUN curl https://bootstrap.pypa.io/get-pip.py -o /tmp/get-pip.py

# Check if the file is downloaded correctly
RUN ls -l /tmp/get-pip.py

# Debugging: Check the contents of get-pip.py to ensure it's downloaded properly
RUN cat /tmp/get-pip.py | head -n 20

# Try installing pip directly via apt-get instead
RUN apt-get install -y python3-pip

# Check pip version to confirm it's installed correctly
RUN pip3 --version

# Debugging: Check if setuptools and wheel are available before installation
RUN python3 -c "import setuptools, wheel; print('Setuptools:', setuptools.__version__, 'Wheel:', wheel.__version__)"

# Install setuptools and wheel before QMK installation, capture logs
RUN pip3 install --upgrade setuptools wheel || tail -n 50 /var/log/apt/term.log

# Install QMK with verbose logging to capture error details
RUN pip3 install -v qmk --break-system-packages || tail -n 50 /var/log/apt/term.log

# Set working directory (use the mounted directory)
WORKDIR /qmk_firmware

# RUN git submodule update --init --recursive

# Start bash shell after QMK is ready
CMD bash
