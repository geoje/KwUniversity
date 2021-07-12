#include "MyIntVector.h"

MyIntVector::MyIntVector() {
	data = new int[DEFAULT_CAPACITY];
	cap = DEFAULT_CAPACITY;
	used = 0;
}
MyIntVector::MyIntVector(size_t capacity) {
	data = new int[capacity];
	cap = capacity;
	used = 0;
}
MyIntVector::MyIntVector(const MyIntVector& v) {
	data = new int[v.cap];
	cap = v.cap;
	used = v.used;
	copy(v.data, v.data + used, data);
}
MyIntVector::~MyIntVector() {
	delete[] data;
}

MyIntVector& MyIntVector::operator=(const MyIntVector& v) {
	int *new_data;
	if (this == &v) return *this;
	if (cap != v.cap) {
		new_data = new int[v.cap];
		delete[] data;
		data = new_data;
		cap = v.cap;
	}
	used = v.used;
	copy(v.data, v.data + used, data);
	return *this;
}
MyIntVector& MyIntVector::operator+=(const MyIntVector& v) {
	if (used + v.used > cap)
		reserve(used + v.used);
	copy(v.data, v.data + v.used, data + used);
	used += v.used;
	return *this;
}
int& MyIntVector::operator[](int index) {
	if (index < 0 || index > (int)used) {
		cerr << "Bad request: Out of range" << endl;
		exit(1);
	}
	return data[index];
}
MyIntVector& MyIntVector::operator+(const MyIntVector& v) {
	if (used != v.used) return *this;
	MyIntVector *result = new MyIntVector(used);
	for (int i = 0; i < (int)used; i++)
		result->push_back(data[i] + v.data[i]);
	return *result;
}
MyIntVector& MyIntVector::operator-(const MyIntVector& v) {
	if (used != v.used) return *this;
	MyIntVector *result = new MyIntVector(used);
	for (int i = 0; i < (int)used; i++)
		result->push_back(data[i] - v.data[i]);
	return *result;
}
int MyIntVector::operator*(const MyIntVector& v)
{
	int result = 0;
	for (int i = 0; i < (int)used; result += data[i] * v.data[i], i++);
	return result;
}
MyIntVector& MyIntVector::operator-() {
	for (int i = 0; i < (int)used; i++)
		data[i] *= -1;
	return *this;
}
bool MyIntVector::operator==(const MyIntVector& v) {
	if (used != v.used) return false;
	for (int i = 0; i < (int)used; i++)
		if (data[i] != v.data[i])
			return false;
	return true;
}

void MyIntVector::pop_back() {
	if (used <= 0) return;
	if (--used <= cap / 2)
		reserve(used);
}
void MyIntVector::push_back(int x) {
	if (used == cap) reserve(cap * 2);
	data[used++] = x;
}
size_t MyIntVector::capacity() const {
	return cap;
}
size_t MyIntVector::size() const {
	return used;
}
bool MyIntVector::isEmpty() const {
	return used == 0;
}
void MyIntVector::clear() {
	delete[] data;
	data = new int[DEFAULT_CAPACITY];
	cap = DEFAULT_CAPACITY;
	used = 0;
}
void MyIntVector::reserve(size_t n) {
	int *larger_array;
	if (n == cap) return;
	if (n < used) n = used;

	larger_array = new int[n];
	copy(data, data + used, larger_array);
	delete[] data;
	data = larger_array;
	cap = n;
}
