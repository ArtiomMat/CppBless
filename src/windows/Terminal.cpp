#include "Terminal.hpp"

#include <cstdlib>
#include <windows.h>

namespace Bless
{
	bool Terminal::fetchSize2()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		{
			throw std::system_error(GetLastError(), std::generic_category(), "lol");
		}
		
		// Some math to get actual size
		width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    	height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

		return true;
	}

	bool Terminal::setInput(bool blocking, bool canonical)
	{
		HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

		DWORD mode;
		if (!GetConsoleMode(hInput, &mode))
		{
			return false;
		}

		if (blocking)
		{
			mode |= ENABLE_LINE_INPUT;
		}
		else
		{
			mode &= ~ENABLE_LINE_INPUT;
		}

		if (canonical)
		{
			write("\e[s\e[?25h\e[u");
			mode |= ENABLE_ECHO_INPUT;
		}
		else
		{
			write("\e[s\e[?25l\e[u");
			mode &= ~ENABLE_ECHO_INPUT;
		}

		SetConsoleMode(hInput, mode);

		return true;
	}

	int Terminal::write(const char* data, unsigned n)
	{
		DWORD ret;
		if (!::WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), data, n, &ret, NULL))
		{
			return -1;
		}
		return ret;
	}

	int Terminal::read(char* data, unsigned n)
	{
		DWORD ret;
		if (!::ReadFile(GetStdHandle(STD_INPUT_HANDLE), data, n, &ret, NULL))
		{
			// We ignore would block
			return GetLastError() == ERROR_NO_DATA ? 0 : -1;
		}
		return ret;
	}

}
