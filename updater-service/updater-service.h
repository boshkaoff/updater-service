// updater-service.h

#ifndef UPDATER_SERVICE_H
#define UPDATER_SERVICE_H

#include <grpcpp/grpcpp.h>
#include "update-service.grpc.pb.h"
#include <string>

constexpr size_t CHUNK_SIZE = 4096;

class UpdaterService final : public update::UpdateService::Service
{
public:
    UpdaterService(
        const std::string& latest_version,
        const std::string& update_file_path
    );

    // Checking latest version
    grpc::Status CheckForUpdates(
        grpc::ServerContext* context,
        const update::CheckRequest* request,
        update::CheckResponse* response
    ) override;

    // Sending latest version
    grpc::Status DownloadUpdate(
        grpc::ServerContext* context,
        const update::DownloadRequest* request,
        grpc::ServerWriter<update::DownloadResponse>* writer
    ) override;

private:
    std::string m_latest_version;
    std::string m_update_file_path;
};

#endif // UPDATER_SERVICE_H
