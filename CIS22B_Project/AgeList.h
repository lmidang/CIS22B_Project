#pragma once

#include <iostream>

#include "BookList.h"

#include "ISBNList.h"



class Age : public BookList {

public:

	Age(Book[], int);

	Age(const BookList&);



	void sortBooks();

	ISBNList getBooks(std::string);

};
