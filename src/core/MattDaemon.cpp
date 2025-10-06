#include "MattDaemon.hpp"
#include "TintinReporter.hpp"

MattDaemon::MattDaemon() {
    Tintin_reporter::info("Starting daemon");
}

MattDaemon::~MattDaemon() {}