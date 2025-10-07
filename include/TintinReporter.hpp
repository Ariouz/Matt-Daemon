#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <time.h>
#include <ctime>

#ifdef BONUS
// Get syslogs: journalctl -f -t matt_daemon
# include <syslog.h>

#endif

class Tintin_reporter {

    private:
        Tintin_reporter(const std::string& logfile);

        std::string _logfile;
        void        _log(const std::string& level, const std::string& msg);

        void        _createLogFile();
        std::string _getTimestamp();

    public:
        Tintin_reporter() = default;
        Tintin_reporter(const Tintin_reporter& other) = default;
        Tintin_reporter& operator=(const Tintin_reporter& other) = default;
        ~Tintin_reporter() = default;

        static Tintin_reporter& instance() {
            static Tintin_reporter _instance("/var/log/matt_daemon/.matt_daemon.log");
            return _instance;
        }

        static void info(const std::string& message);
        static void warn(const std::string& message);
        static void error(const std::string& message);

};
