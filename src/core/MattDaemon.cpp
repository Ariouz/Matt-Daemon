#include "MattDaemon.hpp"
#include "DaemonLocker.hpp"
#include "Server.hpp"

#ifdef BONUS
# include "WebHookNotifier.hpp"
# endif

MattDaemon::MattDaemon() {
    int pid = fork();

    if (pid == -1) throw std::runtime_error("Failed to fork daemon");

    if (pid == 0) {
        if (setsid() == -1) throw std::runtime_error("setsid failed");
        if (chdir("/") == -1) throw std::runtime_error("chdir failed");

        DaemonLocker locker;
        Tintin_reporter::info("Starting daemon");
        #ifdef BONUS
        WebHookNotifier::send("Daemon started");
        #endif

        Server server;
        setup_signals(server);
        server.open();

        while (server.isRunning()) {
            server.loop();
        }

        #ifdef BONUS
        WebHookNotifier::send("Daemon stopped");
        #endif

    }
}

MattDaemon::~MattDaemon() {}