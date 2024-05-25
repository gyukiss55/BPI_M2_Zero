
// BPI_M2_ZERO_TCPIP.cpp
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 8080
#define SOCKET_BUFFER_SIZE 65507

int TCPIP_Server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[SOCKET_BUFFER_SIZE] = { 0 };
    const char* hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    std::cout << "BPI-M2-Zero server started, buffer size:" << SOCKET_BUFFER_SIZE << std::endl;

    while (true) {
        ssize_t valread = recv(new_socket, buffer, SOCKET_BUFFER_SIZE, 0);
        if (valread > 0) {
            std::cout << "Received: " << buffer << std::endl;
            memset(buffer, 0, BUFFER_SIZE);  // Clear the buffer

            sprintf("BPI-M2-Zero received %d data.", valread);
            send(new_socket, buffer, strlen(buffer), 0);
            std::cout << "BPI-M2-Zero received:" << valread << std::endl;
        }
        else if (valread == 0) {
            std::cout << "Client disconnected" << std::endl;
            break;
        }
        else {
            perror("Receive failed");
            break;
        }
    }
    // Read data from the client
 //   int valread = read(new_socket, buffer, 1024);
 //   std::cout << "Message from client: " << buffer << std::endl;

    // Send a response to the client
 //   send(new_socket, hello, strlen(hello), 0);
//  std::cout << "Hello message sent\n";

    // Close the socket
    close(new_socket);
    close(server_fd);

    return 0;
}

int TCPIP_Client(const char *ipAddress) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char* hello = "BPI-M2-Zero client";
    char buffer[SOCKET_BUFFER_SIZE] = { 0 };

    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "\n Socket creation error \n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, ipAddress, &serv_addr.sin_addr) <= 0) {
        std::cout << "\nInvalid address/ Address not supported \n";
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "\nConnection Failed \n";
        return -1;
    }

    // Send data to the server
    send(sock, hello, strlen(hello), 0);
    std::cout << "Hello message sent\n";

    // Read response from the server
    int valread = read(sock, buffer, SOCKET_BUFFER_SIZE);
    std::cout << "Message from server: " << buffer << std::endl;

    // Close the socket
    close(sock);

    return 0;
}
