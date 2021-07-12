#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

class MyIntVector {
public:
	/* Constructor */
	MyIntVector();
	/*	precondition : capacity must be more than 0.
		postcondition: this.data is dynamic allocated as much as capacity */
	MyIntVector(size_t capacity);
	/*	precondition : v is available.
		postcondition: The elements of this.data and v.data are completely identical.
			this.cap is the same as v.cap.
			this.used is the same as v.used. */
	MyIntVector(const MyIntVector& v);

	/* Destructors */
	~MyIntVector();

	/* Operator Overloading */
	/*	precondition : v don't direct self.
			v.cap is not zero. (more than 0)
			v has more than one data.
		postcondition: The elements of this.data and v.data are completely identical.
			this.cap is the same as v.cap.
			this.used is the same as v.used.
			returning dereferencing this. */
	MyIntVector& operator=(const MyIntVector& v);
	/*	precondition : this.data is dynamic allocated.
		postcondition: this.data is appended by v.data.
			returning dereferencing this. */
	MyIntVector& operator+=(const MyIntVector& v);
	/*	precondition : index must be greater than or equal to 0.
		postcondition: returning 'index'th data. */
	int& operator[](int index);
	/*	precondition : v.used must be same as v.used.
		postcondition: returning new MyIntVector with element all merged into
			elements of this.data and v.data. */
	MyIntVector& operator+(const MyIntVector& v);
	/*	precondition : v.used must be same as v.used.
		postcondition: returning new MyIntVector with element all subtract
			elements of this.data and v.data. */
	MyIntVector& operator-(const MyIntVector& v);
	/*	precondition : v.used must be same as v.used.
		postcondition: returning sum of multiplicatinn of elements at the same index */
	int operator*(const MyIntVector& v);
	/*	precondition : this.data must have as many elements as this.used.
		postcondition: returning this those value is inverted with -1 */
	MyIntVector& operator-();
	/*	precondition : v.used must be same as v.used.
		postcondition: returning same for all elements */
	bool operator==(const MyIntVector& v);

	/* Member Functions */
	/*	precondition : this.used is greater than 0.
		postcondition: the last element of this.data is removed. */
	void pop_back();
	/*	precondition : x is available.
		postcondition: x is appended at the last of this.data */
	void push_back(int x);
	/*	precondition : this.cap is available.
		postcondition: returning this.cap. */
	size_t capacity() const;
	/*	precondition : this.used is available.
		postcondition: returning this.used. */
	size_t size() const;
	/*	precondition : this.used is available.
		postcondition: returning wheter there is nothing in this.data.
			(this means that this.used is equal to zero) */
	bool isEmpty() const;
	/*	precondition : this.data is available.
		postcondition: this.data will return it to its original state.
			this.data is dynamic allocated uninitialized state.
			this.cap is zero.
			this.used is zero. */
	void clear();

private:
	/* Const Variables */
	static const size_t DEFAULT_CAPACITY = 20;

	/* Member Variables */
	int *data;
	size_t cap;
	size_t used;

	/* Member Functions */
	/*	precondition : n is not same as this.cap.
			n is greater than this.used.
		postcondition: this.data direct new space that is dynamic allocated with size of n.
			original this.data must be deleted.
			this.cap is same as n. */
	void reserve(size_t n);
};