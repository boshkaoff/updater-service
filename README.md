# 🚀 gRPC Client Update Service

A high-performance gRPC service written in C++ for managing client updates. Designed specifically for Linux environments with CI/CD support for automated builds and testing.

---

## ✨ Features

- **Efficient Updates**: Seamless client updates via gRPC.
- **Version Management**: Tracks and validates client versions.
- **Linux First**: Optimized for deployment on Linux systems.
- **Continuous Integration**: Ready-to-use GitHub Actions CI/CD pipeline.

---

## 🛠️ Technology Stack

- **Language**: C++
- **Framework**: gRPC
- **Serialization**: Protocol Buffers (Protobuf)
- **Build System**: CMake
- **CI/CD**: GitHub Actions

---

## 🚀 Getting Started

### Prerequisites

- **Linux OS** (Tested on Ubuntu 20.04 and later)
- **C++17** or higher
- **gRPC** and **Protobuf** (follow the [official installation guide](https://grpc.io/docs/languages/cpp/quickstart/))
- **CMake 3.15+**

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/boshkaoff/updater-service.git
   cd updater-service
   ```

2. Install dependencies:
   ```bash
   sudo apt update
   sudo apt install -y build-essential cmake libssl-dev protobuf-compiler libprotobuf-dev
   ```

3. Build the gRPC libraries:
   ```bash
   git clone -b v1.55.0 https://github.com/grpc/grpc
   cd grpc
   git submodule update --init
   mkdir -p cmake/build
   cd cmake/build
   cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local ../..
   make -j$(nproc)
   sudo make install
   cd ../../..
   ```

4. Build the project:
```bash
   mkdir build && cd build
   cmake ..
   make -j$(nproc)
```

5. Run the server:
```bash
./server
```
