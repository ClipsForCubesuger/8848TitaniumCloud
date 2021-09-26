#include "Server.h"

Server::Server() {
    create_socket();
    PORT = 8848;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    address_length = sizeof(address);

    bind_socket();
    set_listen();
    accept_connection();
}

void Server::create_socket() {
    if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("[ERROR]: Socket creation failed.");
        exit(EXIT_FAILURE);
    }
    std::cout << "[SERVER]: Socket created successfully.\n";
}

void Server::bind_socket() {
    if (bind(general_socket_descriptor, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("[ERROR]: Socket binding failed.");
        exit(EXIT_FAILURE);
    }
    std::cout << "[SERVER]: Socket bound successfully.\n";
}

void Server::set_listen() {
    if (listen(general_socket_descriptor, 3) < 0) {
        perror("[ERROR]: Listening failed.");
        exit(EXIT_FAILURE);
    }
    std::cout << "[SERVER]: Socket in Listen State (Max Connection Queue: 3).\n";
}

void Server::accept_connection() {
    if ((new_socket_descriptor = accept(general_socket_descriptor, (struct sockaddr *)&address, (socklen_t*)&address_length))<0) {
        perror("[ERROR] : Connecting failed.");
        exit(EXIT_FAILURE);
    }
    std::cout << "[SERVER]: Connection established.\n";
}

void Server::send_file(std::string path) {
    std::fstream file;
    file.open("./backup" + path, std::ios::in | std::ios::binary);
    if (file.is_open()) {
        std::cout << "[SERVER]: File is ready to Transmit.\n";
        std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::cout << "[SERVER]: Transmitting " << contents.length() << " Bytes.\n";
        std::cout << "[SERVER]: Sending...\n";

        int bytes_sent = send(new_socket_descriptor, contents.c_str(), contents.length(), 0 );
        std::cout << "[SERVER]: Transmitted " << bytes_sent << " Bytes.\n";

        std::cout << "[SERVER]: File Transfer Complete.\n";
    } else {
        perror("[ERROR]: File loading failed.");
    }
}
