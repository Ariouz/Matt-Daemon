#include "MattDaemon.hpp"
#include <unistd.h>

int main() {
    int uid = geteuid();
    if (uid != 0) {
        std::cerr << "Daemon must be ran as root user" << std::endl;
        return 1;
    }

    try {
        MattDaemon mattDaemon;
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
