#include "Utils.hpp"

static Server* _server = nullptr;

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
			_server->quit();
			break;
		case SIGTERM:
			Tintin_reporter::info("Signal handler SIGTERM.");
			_server->quit();
			break;
		case SIGHUP:
			Tintin_reporter::info("Signal handler SIGHUP.");
			break;
		case SIGQUIT:
			Tintin_reporter::info("Signal handler SIGQUIT.");
			_server->quit();
			break;
		case SIGUSR1:
			Tintin_reporter::info("Signal handler SIGUSR1.");
			break;
		case SIGUSR2:
			Tintin_reporter::info("Signal handler SIGUSR2.");
			break;
		default:
			Tintin_reporter::info("Received unknown signal.");
			break;
	}
}

void setup_signals(Server& server) {
	_server = &server;

	struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGHUP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}
