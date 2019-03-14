#pragma once

#include <iostream>

#include "BookList.h"

#include "ISBNList.h"



class Publisher : public BookList {

public:

	Publisher(Book[], int);

	Publisher(const BookList&);



	void sortBooks();

	ISBNList getBooks(std::string);

};
