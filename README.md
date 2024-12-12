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
   git clone https://github.com/your-username/grpc-client-update-service.git
   cd grpc-client-update-service

    Install dependencies:

sudo apt update
sudo apt install -y build-essential cmake libssl-dev protobuf-compiler libprotobuf-dev

Build the gRPC libraries:

git clone -b v1.55.0 https://github.com/grpc/grpc
cd grpc
git submodule update --init
mkdir -p cmake/build
cd cmake/build
cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local ../..
make -j$(nproc)
sudo make install
cd ../../..

Build the project:

mkdir build && cd build
cmake ..
make -j$(nproc)

Run the server:

./server
