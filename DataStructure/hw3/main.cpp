#include <iostream>
#include <string>
#include <unordered_map>
#include <ctime>
using namespace std;

int main() {
	int ps_len, ps_frq = 0;
	string text, ps;
	unordered_map<string, int> ps_map;

	/* Read text */
	cin >> ps_len >> text;

	/* Set frequency */
	for(int i = 0, end = text.length() - ps_len; i <= end; ++i) {
		ps = text.substr(i, ps_len);
		++ps_map[ps];
	}

	/* Search frequency */
	for(auto ps_itr = ps_map.begin(); ps_itr != ps_map.end(); ++ps_itr)
		if (ps_itr->second > ps_frq) {
			ps = ps_itr->first;
			ps_frq = ps_itr->second;
		}

	/* Print password */
	cout << ps << endl;
	return 0;
}
