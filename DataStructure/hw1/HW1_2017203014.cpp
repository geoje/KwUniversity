#include "MyIntVector.h"
#include <time.h>

void printVector(MyIntVector& vec, const char* name = NULL) {
	if (name != NULL) cout << "[" << name << "] ";
	if (vec.isEmpty()) {
		cout << "Empty" << endl;
		return;
	}
	cout << vec[0];
	for (int i = 1; i < (int)vec.size(); i++)
		cout << ", " << vec[i];
	cout << endl;
}

void statVector(MyIntVector& vec, const char* name = NULL) {
	if (name != NULL) cout << "[" << name << "] ";
	cout << "Capacity: " << vec.capacity() << ", Used: " << vec.size() << endl;
}

int main() {
	/* Test-1 */
	cout << "<Test-1>" << endl;
	MyIntVector mVec1;
	printVector(mVec1, "mVec1");
	for (int i = 0; i < (int)mVec1.capacity(); i++)
		mVec1.push_back(i * 5);
	printVector(mVec1, "mVec1");
	cout << endl << endl;

	/* Test-2 */
	cout << "<Test-2>" << endl;
	statVector(mVec1, "mVec1 - Before");
	for (int i = 0; i < 5; i++)
		mVec1.push_back(i * 3);
	statVector(mVec1, "mVec1 - After");
	printVector(mVec1, "mVec1 - After");
	cout << endl << endl;

	/* Test-3 */
	cout << "<Test-3>" << endl;
	MyIntVector mVec2 = mVec1;
	statVector(mVec2, "mVec2");
	printVector(mVec2, "mVec2");
	cout << endl << endl;

	/* Test-4 */
	cout << "<Test-4>" << endl;
	statVector(mVec2, "mVec2 - Before");
	for (int i = mVec2.size() / 2; i > 0; i--)
		mVec2.pop_back();
	statVector(mVec2, "mVec2 - After");
	statVector(mVec1, "mVec1 - Before");
	mVec1 = mVec2;
	statVector(mVec1, "mVec1 - After");
	cout << endl << endl;

	/* Test-5 */
	cout << "<Test-5>" << endl;
	statVector(mVec1, "mVec1 - Before");
	printVector(mVec2, "mVec1 - Before");
	statVector(mVec2, "mVec2 - Before");
	printVector(mVec2, "mVec2 - Before");
	mVec1 += mVec2;
	statVector(mVec1, "mVec1 - After");
	printVector(mVec1, "mVec1 - After");
	cout << endl << endl;

	/* Test-6 */
	cout << "<Test-6>" << endl;
	mVec1.clear();
	mVec2.clear();
	srand((size_t)time(NULL));
	for (int i = 0; i < 3; i++) {
		mVec1.push_back(rand() % 10);
		mVec2.push_back(rand() % 10);
	}
	printVector(mVec1, "mVec1");
	printVector(mVec2, "mVec2");
	MyIntVector mVec3 = mVec1 + mVec2;
	statVector(mVec3, "mVec1 + mVec2");
	printVector(mVec3, "mVec1 + mVec2");
	mVec3 = mVec1 - mVec2;
	printVector(mVec3, "mVec1 - mVec2");
	cout << endl << endl;

	/* Test-7 */
	cout << "<Test-7>" << endl;
	printVector(mVec1, "mVec1");
	printVector(mVec2, "mVec2");
	cout << "[mVec1 * mVec2] " << mVec1 * mVec2;
	cout << endl << endl;

	/* Test-8 */
	cout << "<Test-8>" << endl;
	printVector(mVec1, "mVec1");
	printVector(-mVec1, "-mVec1");
	cout << endl << endl;

	/* Test-9 */
	cout << "<Test-9>" << endl;
	printVector(mVec1, "mVec1");
	printVector(mVec2, "mVec2");
	if (mVec1 == mVec2) cout << "Oh my god! Same!!!!" << endl;
	else  cout << "Ha. Not Same..." << endl;
	mVec1 = mVec2;
	printVector(mVec1, "mVec1");
	printVector(mVec2, "mVec2");
	if (mVec1 == mVec2) cout << "Oh my god! Same!!!!" << endl;
	else  cout << "Ha. Not Same..." << endl;
	cout << endl << endl;

	/* Test - 10 */
	cout << "<Test-10>" << endl;
	mVec1.clear();
	mVec2.clear();
	mVec3.clear();
	for (int i = 0; i < 4; i++) {
		mVec1.push_back(rand() % 10);
		mVec2.push_back(rand() % 10);
		mVec3.push_back(rand() % 10);
	}
	printVector(mVec1, "mVec1 - After");
	printVector(mVec2, "mVec2 - After");
	printVector(mVec3, "mVec3 - After");
	mVec1 = mVec2 = mVec3;
	printVector(mVec1, "mVec1 - After");
	printVector(mVec2, "mVec2 - After");
	printVector(mVec3, "mVec3 - After");
	cout << endl << endl;

	/* Test-11 */
	cout << "<Test-11>" << endl;
	mVec1[100];
	cout << "mVec1[100] can read!" << endl;

	return 0;
}