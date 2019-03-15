#pragma once
#include <iostream>
#include "BookList.h"

class ISBNList : public BookList {
public:
	ISBNList();
	ISBNList(Book[], int);
	ISBNList(const BookList&);

	void sortBooks();
	Book getBook(unsigned long long);
};