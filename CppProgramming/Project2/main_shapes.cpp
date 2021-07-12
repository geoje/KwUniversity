#include "Graph.h"
#include "Simple_window.h"
using namespace Graph_lib;

int main() {
	srand(time(nullptr));
	Simple_window win(Point(100, 100), 800, 800, "fltk_ygh");
	for (int idx = 0; idx < 3; idx++)
		switch (idx) {
		case 0: { //Box
			vector<Box*> boxs;
			for (int y = 0; y < win.y_max(); y += 200)
				for (int x = 0; x < win.x_max(); x += 200) {
					int w = rand() % 120 + 40;
					int h = rand() % 120 + 40;
					int r = rand() % (min(w, h) / 2);
					boxs.push_back(new Box(Point(x + (100 - w / 2), y + (100 - h / 2)), w, h, r));
				}

			for (int i = 0; i < boxs.size(); i++) {
				boxs[i]->set_color(rand() % 14);
				boxs[i]->set_fill_color(rand() % 14);
				win.attach(*boxs[i]);
			}
			win.wait_for_button();
			for (int i = 0; i < boxs.size(); i++)
				win.detach(*boxs[i]);
			break;
		}

		case 1: { //Regular_polygon
			vector<Regular_polygon*> polygons;
			for (int y = 100; y < win.y_max(); y += 200)
				for (int x = 100; x < win.x_max(); x += 200) {
					int n = rand() % 6 + 3;
					int r = rand() % 60 + 20;
					polygons.push_back(new Regular_polygon(Point(x, y), n, r));
				}

			for (int i = 0; i < polygons.size(); i++) {
				polygons[i]->set_color(rand() % 14);
				polygons[i]->set_fill_color(rand() % 14);
				win.attach(*polygons[i]);
			}
			win.wait_for_button();
			for (int i = 0; i < polygons.size(); i++)
				win.detach(*polygons[i]);
			break;
		}

		case 2: { //Star
			vector<Star*> stars;
			for (int y = 100; y < win.y_max(); y += 200)
				for (int x = 100; x < win.x_max(); x += 200) {
					int n = rand() % 6 + 3;
					int r1 = rand() % 60 + 20;
					int r2 = rand() % 60 + 20;
					stars.push_back(new Star(Point(x, y), n, r1, r2));
				}

			for (int i = 0; i < stars.size(); i++) {
				stars[i]->set_color(rand() % 14);
				stars[i]->set_fill_color(rand() % 14);
				win.attach(*stars[i]);
			}
			win.wait_for_button();
			for (int i = 0; i < stars.size(); i++)
				win.detach(*stars[i]);
			break;
		}
	}
}