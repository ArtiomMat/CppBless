#include "Bless.hpp"

#include <cstdlib>
#include <cstring>
#include <cstdlib>

namespace Bless
{
	Terminal::Terminal()
	{
		if (!setInput(false, false))
		{
			puts("Bless: Terminal failed to enter into raw input.");
		}
	}

	Terminal::~Terminal()
	{
		setInput(true, true);
	}

	bool Terminal::fetchSize()
	{
		if (!fetchSize2())
		{
			return false;
		}
		
		glyphs = static_cast<Glyph*>(
			realloc(glyphs, width * height * sizeof (*glyphs))
		);

		return true;
	}

	int Terminal::write(const char* data)
	{
		return write(data, strlen(data));
	}

	// I am unsure if it will work, I just theorize that it exists in Window's terminal.
	bool Terminal::hasTrueColor() noexcept
	{
		char* colorterm = getenv("COLORTERM");
		if (colorterm == NULL || strcmp(colorterm, "truecolor"))
		{
			return false;
		}

		return true;
	}

	void Terminal::render()
	{
		str.clear();
		str += "\e[H";
		for (unsigned i = 0; i < width * height; i++)
		{
			// An invalid ASCII character
            if (glyphs[i].c < ' ')
			{
                str += "\e[0m ";
                continue;
            }
            // Background color
            str += "\e[0";
            
            // Background color
            switch (glyphs[i].bg.t)
			{
                case ColorType::Black:
				str += ";100";
				break;
                case ColorType::Red:
				str += ";101";
				break;
                case ColorType::Green:
				str += ";102";
				break;
                case ColorType::Yellow:
				str += ";103";
				break;
                case ColorType::Blue:
				str += ";104";
				break;
                case ColorType::Purple:
				str += ";105";
				break;
                case ColorType::Cyan:
				str += ";106";
				break;
                case ColorType::White:
				str += ";107";
				break;
    
                case ColorType::DBlack:
				str += ";40";
				break;
                case ColorType::DRed:
				str += ";41";
				break;
                case ColorType::DGreen:
				str += ";42";
				break;
                case ColorType::DYellow:
				str += ";43";
				break;
                case ColorType::DBlue:
				str += ";44";
				break;
                case ColorType::DPurple:
				str += ";45";
				break;
                case ColorType::DCyan:
				str += ";46";
				break;
                case ColorType::DWhite:
				str += ";47";
				break;

                case ColorType::_TrueColor:
				str += ";48;2;";
				str += std::to_string(glyphs[i].bg.rgb[0]);
				str += ";";
				str += std::to_string(glyphs[i].bg.rgb[1]);
				str += ";";
				str += std::to_string(glyphs[i].bg.rgb[2]);
				break;

				default:;
            }
            // Foreground color
            switch (glyphs[i].fg.t)
			{
                case ColorType::Black:
				str += ";90";
				break;
                case ColorType::Red:
				str += ";91";
				break;
                case ColorType::Green:
				str += ";92";
				break;
                case ColorType::Yellow:
				str += ";93";
				break;
                case ColorType::Blue:
				str += ";94";
				break;
                case ColorType::Purple:
				str += ";95";
				break;
                case ColorType::Cyan:
				str += ";96";
				break;
                case ColorType::White:
				str += ";97";
				break;

                case ColorType::DBlack:
				str += ";30";
				break;
                case ColorType::DRed:
				str += ";31";
				break;
                case ColorType::DGreen:
				str += ";32";
				break;
                case ColorType::DYellow:
				str += ";33";
				break;
                case ColorType::DBlue:
				str += ";34";
				break;
                case ColorType::DPurple:
				str += ";35";
				break;
                case ColorType::DCyan:
				str += ";36";
				break;
                case ColorType::DWhite:
				str += ";37";
				break;

                case ColorType::_TrueColor:
				str += ";38;2;";
				str += std::to_string(glyphs[i].fg.rgb[0]);
				str += ";";
				str += std::to_string(glyphs[i].fg.rgb[1]);
				str += ";";
				str += std::to_string(glyphs[i].fg.rgb[2]);
				break;

				default:;
            }

            // Flags
            if (glyphs[i].fl & GLYPH_BOLD)
			{
                str += ";1";
            }
            if (glyphs[i].fl & GLYPH_LIGHT)
			{
                str += ";2";
            }
            if (glyphs[i].fl & GLYPH_ITALIC)
			{
                str += ";3";
            }
            if (glyphs[i].fl & GLYPH_LINE)
			{
                str += ";4";
            }
            if (glyphs[i].fl & GLYPH_BLINK)
			{
                str += ";5";
            }
            if (glyphs[i].fl & GLYPH_STRIKE)
			{
                str += ";9";
            }

            str += 'm';
            str += glyphs[i].c;
		}

		write(str.c_str(), str.size());
	}
}
