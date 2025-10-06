#include "DaemonLocker.hpp"
#include "TintinReporter.hpp"

DaemonLocker::DaemonLocker() {
    std::filesystem::path path = _file;
    std::filesystem::path parent = path.parent_path();
    if (!parent.empty() && !std::filesystem::exists(parent)) {
        try {
            if (!std::filesystem::create_directories(parent)) {
                throw std::runtime_error("Failed to created lock parent directories");
            }
        } catch (std::filesystem::filesystem_error& e) {
            throw std::runtime_error(e.what());
        }
    }

    if (std::filesystem::exists(_file)) {
        throw std::runtime_error("Cannot run multiple daemon at the same time");
    }

    std::ofstream ofs(_file, std::ios::out | std::ios::trunc);
    
    if (ofs.is_open()) {
        ofs << getpid() << std::endl;
        ofs.close();
        return;
    } 
    
    throw std::runtime_error("Failed to create lock file due to permissions or FS error");
}

DaemonLocker::~DaemonLocker() {
    std::filesystem::path path = _file;

    if (!std::filesystem::exists(path)) Tintin_reporter::error("Lock file not found");
    
    if (std::filesystem::remove(path) != 0) Tintin_reporter::error("Failed to delete lock file");
}