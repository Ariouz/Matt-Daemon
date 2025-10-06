#include "MattDaemon.hpp"
#include "TintinReporter.hpp"
#include "DaemonLocker.hpp"

MattDaemon::MattDaemon() {
    int pid = fork();

    if (pid == -1) throw std::runtime_error("Failed to fork daemon");

    if (pid == 0) {
        DaemonLocker locker;
        Tintin_reporter::info("Starting daemon");

        // start server
    }
}

MattDaemon::~MattDaemon() {}