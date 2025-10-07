#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <cerrno>
#include <cstring>

#include "TintinReporter.hpp"

class DaemonLocker {

    private:
        std::string _file = "/var/lock/matt_daemon.lock";
        int         _fd;

    public:
        DaemonLocker();
        DaemonLocker& operator=(const DaemonLocker& other) = default;
        DaemonLocker(const DaemonLocker& other) = default;
        ~DaemonLocker();

};