#pragma once

#include <iostream>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include <mutex>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>
#include <atomic>

class MattShell {

    private:
        char*               _readline_return;
        int                 _serverSock;
        std::atomic<bool>   _running{true};

    public:
        MattShell(int serverSock);
        MattShell& operator=(const MattShell& other) = default;
        MattShell(const MattShell& other) = default;
        ~MattShell() = default;


        static void	                sigint_handler(int signum);
        void	                    signal(void);
        void                        set_termios_handle( void );
        void                        readline_util( void );

        bool                        isRunning();
        void                        setRunning(bool running);

};