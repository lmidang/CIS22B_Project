#pragma once

#include <iostream>

#include "BookList.h"

#include "ISBNList.h"



class Quantity : public BookList {

public:

	Quantity(Book[], int);

	Quantity(const BookList&);



	void sortBooks();

	ISBNList getBooks(std::string);

};
