// AbyssLeague update service (2024)
//

#include "updater-service.h"
#include <grpcpp/grpcpp.h>
#include <iostream>

// Forward declaration

void RunServer(
    const std::string& server_address, 
    const std::string& latest_version, 
    const std::string& update_file_path
);

// Main
int main( int )

{
    const std::string server_address = "0.0.0.0:50051";
    const std::string latest_version = "2.0.0";
    const std::string update_file_path = "files/client_release.exe";

    RunServer(server_address, latest_version, update_file_path);

    return 0;
}


// Methods implementation

void RunServer(
    const std::string& server_address,
    const std::string& latest_version,
    const std::string& update_file_path
) 
{
    UpdaterService service(latest_version, update_file_path);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    std::cout << "[Log]" << "Update service is running on " << server_address << std::endl;
    std::cout << "[Log]" << "Update service working." << std::endl;
    
    server->Wait();
}
