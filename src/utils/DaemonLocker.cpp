#include "DaemonLocker.hpp"

DaemonLocker::DaemonLocker() : _fd(-1) {
    std::filesystem::path path = _file;
    std::filesystem::path parent = path.parent_path();
    if (!parent.empty() && !std::filesystem::exists(parent)) {
        std::filesystem::create_directories(parent);
    }
    
    _fd = open(_file.c_str(), O_CREAT | O_RDWR, 0644);
    if (_fd == -1) {
        throw std::runtime_error("Failed to open lock file");
    }
    
    if (flock(_fd, LOCK_EX | LOCK_NB) == -1) {
        close(_fd);
        throw std::runtime_error("Can't open :/var/lock/matt_daemon.lock");
    }
    
    std::ofstream ofs(_file, std::ios::trunc);
    ofs << getpid() << std::endl;
}

DaemonLocker::~DaemonLocker() {
    if (_fd != -1) {
        close(_fd);
    }
    std::filesystem::remove(_file);
}
