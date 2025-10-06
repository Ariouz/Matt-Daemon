#pragma once

#include <iostream>
#include <string.h>

#include "TintinReporter.hpp"

class MattDaemon {

    public:
        MattDaemon();
        MattDaemon(const MattDaemon& other) = default;
        MattDaemon& operator=(const MattDaemon& other) = default;
        ~MattDaemon();

};
