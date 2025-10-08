#include "TintinReporter.hpp"
#include "Utils.hpp"

Tintin_reporter::Tintin_reporter(const std::string& logfile) : _logfile(logfile) {
    _createLogFile();    
}

void Tintin_reporter::info(const std::string& msg) { 
    instance()._log("[INFO] ", msg);
    #ifdef BONUS
    openlog("matt_daemon", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "%s", msg.c_str());
    closelog();
    #endif
}

void Tintin_reporter::warn(const std::string& msg) { 
    instance()._log("[WARN] ", msg); 
    #ifdef BONUS
    openlog("matt_daemon", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_WARNING, "%s", msg.c_str());
    closelog();
    #endif
}

void Tintin_reporter::error(const std::string& msg) { 
    instance()._log("[ERROR] ", msg);
    #ifdef BONUS
    openlog("matt_daemon", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_ERR, "%s", msg.c_str());
    closelog();
    #endif
}

void Tintin_reporter::_log(const std::string& level, const std::string& msg) {
    std::ofstream ofs(_logfile, std::ofstream::out | std::ofstream::app);
    std::stringstream ss;
    ss << _getTimestamp() << " " << level << msg << std::endl;
    ofs << ss.str();
}

std::string Tintin_reporter::_getTimestamp() {
    std::time_t now = std::time(0);
    std::tm *local_time = std::localtime(&now);
    char buffer[22];
    std::strftime(buffer, sizeof(buffer), "[%d/%m/%Y-%H:%M:%S]", local_time);
    return std::string(buffer);
}

void Tintin_reporter::_createLogFile() {
    std::filesystem::path path = _logfile;

    if (std::filesystem::exists(path)) {
        std::ofstream ofs(_logfile, std::ofstream::out | std::ofstream::trunc);
        if (!ofs.is_open()) {
            throw std::runtime_error("Failed to open logfile : " + _logfile);
        }
        return ;
    }

    std::filesystem::path parent = path.parent_path();
    if (!parent.empty() && !std::filesystem::exists(parent)) {
        try {
            if (!std::filesystem::create_directories(parent)) {
                throw std::runtime_error("Failed to created log's parent directories");
            }
        } catch (std::filesystem::filesystem_error& e) {
            throw std::runtime_error(e.what());
        }
    }

    std::ofstream ofs(_logfile, std::ofstream::out | std::ofstream::trunc);
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to create/open logfile : " + _logfile);
    }
}

void Tintin_reporter::compresss() {
    std::string timestamp = instance()._getTimestamp();
    for (char &c : timestamp) {
        if (c == '/' || c == ':' || c == '[' || c == ']' || c == ' ')
            c = '_';
    }
    std::string gz = (instance()._logfile + timestamp + ".gz");
    info("Compressing log to " + gz);
    compress_log(instance()._logfile.c_str(), gz.c_str());
}