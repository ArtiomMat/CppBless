#pragma once

#include "Glyph.hpp"

#include <string>
#include <system_error>

namespace Bless
{
	// A class that wraps around terminal functionality, this is the interface for the terminal.
	// The singleton is not thread-safe, you should use a mutex.
	class Terminal {
		public:
		// The size of this flattened array is defined by size
		Glyph* glyphs = nullptr;
		// Updated via fetchSize()
		union
		{
			unsigned size[2] = {0};
			
			struct
			{
				unsigned width, height;
			};
		};

		// Getting an instance of Terminal forces STDIN into raw and nonblocking mode, and also the cursor is hidden. You can revert this any time with setInput(false, false). 
		static Terminal& instance() {
			static Terminal i;
			return i;
		}
		
		Terminal(Terminal const&) = delete;
		void operator=(Terminal const&) = delete;

		// Returns if operation succeeded.
		static bool setInput(bool blocking, bool canonical);
		// Check if the terminal supports direct color
		bool hasTrueColor() noexcept;
		// Updates the size member. Returns false if couldn't properly get the size. Throws system_error if fails to fetch the size properly, because this is a serious problem.
		bool fetchSize();
		// Raw write call wrapper. Returns how much was written. <0 will indicate error.
		static int write(const char* data, unsigned n);
		// Same as regular write, but assumes that it's a string. So very important you make sure that there is a null-terminator.
		static int write(const char* data);
		// Raw read call wrapper. Returns how much was read. <0 will indicate error.
		// Note that EWOULDBLOCK errors are ignored because they are not errors in this context.
		static int read(char* data, unsigned n);
		
		// Call fetchSize() before this, otherwise there will be problems.
		// A higher level function that renders the glyphs to the screen after they were modified.
		void render();

		// Unsafe
		inline void put(const Glyph& g, unsigned x, unsigned y) noexcept
		{
			glyphs[x + y * width] = g;
		}
		// Unsafe
		inline Glyph& get(unsigned x, unsigned y) noexcept
		{
			return glyphs[x + y * width];
		}

		private:
		// Stores the string to be written out into the terminal
		std::string str;

		Terminal();
		~Terminal();

		// Helper function, includes system specific stuff.
		bool fetchSize2();
	};
}

