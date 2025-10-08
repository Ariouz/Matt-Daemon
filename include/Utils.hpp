# pragma once

# include <vector>
# include <string>
# include <unistd.h>
# include <sstream>
# include <signal.h>
# include <zlib.h>
# include <fstream>
# include <iostream>
# include "TintinReporter.hpp"
# include "Server.hpp"

class Server;

std::vector<std::string>    splitByCr(const std::string& input);
void                        signal_handler(int sig);
void                        setup_signals(Server& server);

int                         compress_log(const char* src, const char* dest);
