#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unistd.h>

#include "TintinReporter.hpp"

class DaemonLocker {

    private:
        std::string _file = "/var/lock/matt_daemon.lock";

    public:
        DaemonLocker();
        DaemonLocker& operator=(const DaemonLocker& other) = default;
        DaemonLocker(const DaemonLocker& other) = default;
        ~DaemonLocker();

};