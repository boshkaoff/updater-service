// updater-service.cpp

#include "updater-service.h"

#include <fstream>
#include <iostream>

UpdaterService::UpdaterService(
    const std::string& latest_version,
    const std::string& update_file_path
)
    : 
    m_latest_version(latest_version),
    m_update_file_path(update_file_path)
{}

grpc::Status UpdaterService::CheckForUpdates(
    grpc::ServerContext* context,
    const update::CheckRequest* request,
    update::CheckResponse* response
)
{
    if (request->current_version() != m_latest_version) {
        response->set_update_available(true);
        response->set_latest_version(m_latest_version);
    }
    else {
        response->set_update_available(false);
    }
    return grpc::Status::OK;
}

grpc::Status UpdaterService::DownloadUpdate(
    grpc::ServerContext* context,
    const update::DownloadRequest* request,
    grpc::ServerWriter<update::DownloadResponse>* writer
)
{
    std::ifstream file(m_update_file_path, std::ios::binary);
    if (!file) {
        return grpc::Status(grpc::StatusCode::NOT_FOUND, "No file");
    }

    char buffer[CHUNK_SIZE];
    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        update::DownloadResponse response;
        response.set_chunk(buffer, file.gcount());
        writer->Write(response);
    }

    return grpc::Status::OK;
}
