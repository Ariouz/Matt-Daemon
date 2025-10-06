#pragma once

# include <iostream>
# include <fcntl.h>
# include <poll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <vector>
# include <unistd.h>
# include <cstring>

# include "TintinReporter.hpp"
# include "Utils.hpp"

# define SERVER_PORT 4242
# define SERVER_MAXCON 3

class Server {

    private:
        bool                        _running;
        int                         _serverFd;
        std::vector<struct pollfd>	_polls;

    public:
        Server();
        Server(const Server& other) = default;
        Server& operator=(const Server& other) = default;
        ~Server();


        void    open();
        void    quit();
        void    loop();
        void	acceptClient(void);
        void    acceptData(int fd);
        void    clearClient(int fd);

        bool    isRunning() const;

};