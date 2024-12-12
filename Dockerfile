# Этап сборки
FROM ubuntu:22.04 AS builder

# Установка зависимостей
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    protobuf-compiler \
    git \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Установка gRPC из репозитория
RUN git clone -b v1.51.1 --depth 1 --recurse-submodules https://github.com/grpc/grpc /tmp/grpc && \
    mkdir -p /tmp/grpc/cmake/build && \
    cd /tmp/grpc/cmake/build && \
    cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release ../.. && \
    make -j$(nproc) && \
    make install && \
    ldconfig && \
    rm -rf /tmp/grpc

WORKDIR /app

# Копируем исходный код проекта
COPY . .

# Сборка проекта
RUN mkdir -p build && cd build && \
    cmake -DCMAKE_PREFIX_PATH="/usr/local" .. && \
    cmake --build . -- -j$(nproc)

# Финальный образ
FROM ubuntu:22.04 AS final

# Установка только необходимых пакетов
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /root/

# Копируем скомпилированный бинарный файл из builder-образа
COPY --from=builder /app/build/updater_service .

ARG PORT=50051
ENV PORT=${PORT}

EXPOSE ${PORT}

CMD ["./updater_service"]
