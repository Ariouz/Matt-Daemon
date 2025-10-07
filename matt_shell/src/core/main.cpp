#include "MattShell.hpp"

void socket_listener(int sock, MattShell* shell) {
    char buf[1024];
    while (shell->isRunning()) {
        ssize_t n = recv(sock, buf, sizeof(buf)-1, 0);
        if (n <= 0) {
            std::cout << "\nDaemon has closed connection\n";
            shell->setRunning(false);
            exit(0);
        }
        fflush(stdout);
    }
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4242);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock);
        return 1;
    }

    MattShell shell(sock);

    std::thread listener(socket_listener, sock, &shell);
    listener.detach();

    shell.readline_util();

    close(sock);
}


