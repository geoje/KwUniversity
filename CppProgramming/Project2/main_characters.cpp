#include "Graph.h"
#include "Simple_window.h"
#include "Character.h"

using namespace Graph_lib;

int main()
{
	srand(time(nullptr));
	Simple_window win(Point(100, 100), 800, 800, "fltk_ygh");

	vector<Character*> characters;
	characters.push_back(new Evader(&win, 4, 7));
	characters.push_back(new Pursuer(&win, 3, 0));

	characters[0]->setEnemy(characters[1]);
	characters[1]->setEnemy(characters[0]);

	do
	{
		win.wait_for_button();

		for (Character* ch : characters)
		{
			ch->move();
		}
		if (characters[0]->row() == characters[0]->enemy()->row()
			&& characters[0]->col() == characters[0]->enemy()->col())
			break;
	} while (true);

	Graph_lib::Text text_end(Point(300, 400), "The End");
	text_end.set_font_size(60);
	win.attach(text_end);
	win.wait_for_button();
}
