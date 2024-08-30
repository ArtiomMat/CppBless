#pragma once

#include <cinttypes>

namespace Bless
{
	enum ColorType : char
	{
		// Color chosen by the terminal as default in the given context
		Default,

		Black,
		Red,
		Green,
		Yellow,
		Blue,
		Purple,
		Cyan,
		White,

		DBlack,
		DRed,
		DGreen,
		DYellow,
		DBlue,
		DPurple,
		DCyan,
		DWhite,

		// For internal use, do not use.
		_TrueColor,
	};
	
	enum
	{
		GLYPH_BOLD = 1 << 0,
		// Gives the light version of the font, if available.
		GLYPH_LIGHT = 1 << 1,
		// Not supported everywhere.
		GLYPH_ITALIC = 1 << 2,
		// Underline.
		GLYPH_LINE = 1 << 3,
		// Strike-through.
		GLYPH_STRIKE = 1 << 4,
		// Blink a library defined time. Not widely supported.
		GLYPH_BLINK = 1 << 5,
	};

	struct Color
	{
		ColorType t = ColorType::Default;
		uint8_t rgb[3]; // If TrueColor
		
		inline void set(ColorType t) noexcept
		{
			this->t = t;
		}
		void set(uint8_t r, uint8_t g, uint8_t b) noexcept
		{
			t = ColorType::_TrueColor;
			rgb[0] = r;
			rgb[1] = g;
			rgb[2] = b;
		}
	};

	struct Glyph
	{
		char c = 0;
		char fl = 0;
		// Do not set it manually, use setters.
		Color fg, bg;

		inline Glyph(const char c) noexcept
		{
			this->c = c;
		}
	};
}

