#include "Server.hpp"

Server::Server() :  _running(true), _serverFd(-1) {}
Server::~Server() {
    for (std::size_t index = 0; index < this->_polls.size(); index++) {
        close(_polls[index].fd);
    }

    if (_serverFd != -1) {
        close(_serverFd);
        Tintin_reporter::info("Daemon server closed");
    }
}

bool Server::isRunning() const {
    return _running;
}

void Server::open() {
    sockaddr_in     sockaddr;
    struct pollfd   pollfd;

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(SERVER_PORT);
    sockaddr.sin_addr.s_addr = INADDR_ANY;

    _serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverFd == -1) throw std::runtime_error("Failed to create server socket");

    if (bind(_serverFd, (struct sockaddr*) &sockaddr, sizeof(sockaddr)) == -1) throw std::runtime_error("Failed to bind socket");
    Tintin_reporter::info("Server bound to port " + std::to_string(SERVER_PORT));

    if (listen(_serverFd, SERVRE_MAXCON) == -1) throw std::runtime_error("Failed to listen to socket");

    pollfd.fd = _serverFd;
    pollfd.events = POLLIN;
    pollfd.revents = 0;
    
    this->_polls.push_back(pollfd);
    Tintin_reporter::info("Server is ready and listening to port " + std::to_string(SERVER_PORT));
}

void    Server::quit() {
    Tintin_reporter::info("Quit requested");
    _running = false;
}

void	Server::loop() {
	if (poll(&_polls[0], this->_polls.size(), -1) == -1) throw std::runtime_error("Error: poll() function failed");

	for (std::size_t index = 0; index < this->_polls.size(); index++) {
		if (this->_polls[index].revents & POLLIN) {
			if (this->_polls[index].fd == this->_serverFd) {
				this->acceptClient();
			}
			else {
				this->acceptData(this->_polls[index].fd);
			}
		}
	}
}

void	Server::acceptClient(void)
{
	sockaddr_in		client_addr;
	struct pollfd	client_poll_fd;
	int				client_socket_fd;
	socklen_t		client_len;

   

	client_len = sizeof(client_addr);
	client_socket_fd = accept(_serverFd, (sockaddr *)&client_addr, &client_len);

	if (client_socket_fd == -1) throw std::runtime_error("Error: failed to accept client");
	if (fcntl(client_socket_fd, F_SETFL, O_NONBLOCK) == -1) throw std::runtime_error("Error: failed to set client to NONBLOCK");

     if (_polls.size() == SERVRE_MAXCON + 1) {
        close(client_socket_fd);
        return ;
    }

	client_poll_fd.fd = client_socket_fd;
	client_poll_fd.events = POLLIN;
	client_poll_fd.revents = 0;
	this->_polls.push_back(client_poll_fd);
}

void	Server::acceptData(int fd)
{
	char	buffer[1024];
	ssize_t	data;

	std::memset(buffer, 0, sizeof(buffer));

	data = recv(fd, buffer, sizeof(buffer) - 1, 0);
	buffer[1023] = '\0';


	if (data <= 0) {
		this->clearClient(fd);
		return ;
	}

	std::vector<std::string> lines = splitByCr(buffer);

    for (std::size_t index = 0; index < lines.size(); ++index) {
        if (lines[index] == "quit") quit();
        else Tintin_reporter::info("Client: " + std::string(lines[index]));
    }
}

void    Server::clearClient(int fd) {
    for (std::size_t index = 0; index < this->_polls.size(); index++) {
		if (this->_polls[index].fd == fd) this->_polls.erase(this->_polls.begin() + index);
	}
}