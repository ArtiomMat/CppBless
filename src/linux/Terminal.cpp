#include "Bless.hpp"

extern "C"
{
	#include <termios.h>
	#include <unistd.h>
	#include <fcntl.h>
	#include <sys/ioctl.h>
}

#include <cstring>
#include <system_error>

namespace Bless
{
	bool Terminal::fetchSize2()
	{
		struct winsize w;
		if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
		{
			throw std::system_error(errno, std::generic_category(), "lol");
		}

		height = w.ws_row;
		width = w.ws_col;

		return true;
	}

	bool Terminal::setInput(bool blocking, bool canonical)
	{
		static termios t = {0};
		
		if (tcgetattr(STDIN_FILENO, &t) == -1)
		{
			return false;
		}

		if (canonical)
		{
			write("\e[s\e[?25h\e[u");
			t.c_lflag |= (ICANON | ECHO);
		}
		else
		{
			write("\e[s\e[?25l\e[u");
			t.c_lflag &= ~(ICANON | ECHO);
		}

		t.c_cc[VMIN] = blocking ? 1 : 0;

		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &t) == -1)
		{
			return false;
		}

		return true;
	}

	int Terminal::write(const char* data, unsigned n)
	{
		return ::write(STDOUT_FILENO, data, n);
	}

	int Terminal::read(char* data, unsigned n)
	{
		int ret;
		if ((ret = ::read(STDOUT_FILENO, data, n)) == -1)
		{
			// We ignore would block
			return errno == EWOULDBLOCK ? 0 : -1;
		}
		return true;
	}
}
