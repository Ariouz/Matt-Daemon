#include "MattDaemon.hpp"
#include "DaemonLocker.hpp"
#include "Server.hpp"

MattDaemon::MattDaemon() {
    int pid = fork();

    if (pid == -1) throw std::runtime_error("Failed to fork daemon");

    if (pid == 0) {
        DaemonLocker locker;
        Tintin_reporter::info("Starting daemon");

        Server server;
        server.open();

        while (server.isRunning()) {
            server.loop();
        }
    }
}

MattDaemon::~MattDaemon() {}