#pragma once
#include <iostream>
#include "BookList.h"
#include "ISBNList.h"

class AuthorList : public BookList {
public:
	AuthorList(Book[], int);
	AuthorList(const BookList&);

	void sortBooks();
	ISBNList getBooks(std::string);
};