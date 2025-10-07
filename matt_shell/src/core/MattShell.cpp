#include "MattShell.hpp"

MattShell::MattShell(int serverSock) : _serverSock(serverSock) {}

void	MattShell::set_termios_handle(void) {
	struct termios	termios_p;

	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
}

void	MattShell::sigint_handler(int signum) {
	(void) signum;

    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	MattShell::signal(void) {
	struct sigaction	action;

	action.sa_handler = MattShell::sigint_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
}


void    MattShell::readline_util( void ) {
    set_termios_handle();
    signal();
    while (isRunning()) {
        this->_readline_return = readline("\033[38;5;154mMattShell> \033[0m");

        if (!this->_readline_return)
            exit(0);

        if (this->_readline_return && *this->_readline_return)
            add_history(this->_readline_return);

        if (this->_readline_return) {
            std::string command = this->_readline_return;

            send(_serverSock, command.c_str(), strlen(command.c_str()), 0);

            free(this->_readline_return);
        }
    }
}

bool    MattShell::isRunning() {
    return _running.load();
}

void    MattShell::setRunning(bool running) {
    _running.store(running);
}