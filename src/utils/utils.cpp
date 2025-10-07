#include "Utils.hpp"

std::vector<std::string> splitByCr(const std::string& input) {
    std::vector<std::string>    result;
    std::istringstream          iss(input);
    std::string                 line;

    while (std::getline(iss, line, '\n')) {
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.resize(line.size() - 1);
        }
        result.push_back(line);
    }

    return result;
}

void signal_handler(int sig) {
	switch (sig) {
		case SIGINT:
			Tintin_reporter::info("Signal handler SIGINT.");
			break;
		case SIGTERM:
			Tintin_reporter::info("Signal handler SIGTERM.");
			break;
		case SIGHUP:
			Tintin_reporter::info("Signal handler SIGHUP.");
			break;
		case SIGQUIT:
			Tintin_reporter::info("Signal handler SIGQUIT.");
			break;
		case SIGUSR1:
			Tintin_reporter::info("Signal handler SIGUSR1.");
			break;
		case SIGUSR2:
			Tintin_reporter::info("Signal handler SIGUSR2.");
			break;
		default:
			Tintin_reporter::info("Received unknown signal.");
	}
    Tintin_reporter::info("Quit requested");
}

void setup_signals(void) {
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGHUP, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
}
