#include "Bless.hpp"

#include <cstdio>

int main()
{
	auto& term = Bless::Terminal::instance();

	term.fetchSize();
	Bless::Glyph a = 'x';
	a.fg.set(255, 0, 0);
	a.bg.set(Bless::ColorType::Blue);

	term.put(a, 1, 2);

	term.render();

	term.setInput(true, false);

	char x;
	term.read(&x, 1);

	return 0;
}
