#pragma once
#include <iostream>
#include "BookList.h"
#include "ISBNList.h"

class TitleList : public BookList {
public:
	TitleList(Book[], int);
	TitleList(const BookList&);

	void sortBooks();
	ISBNList getBooks(std::string);
};