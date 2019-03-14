#pragma once

#include <iostream>

#include "BookList.h"

#include "ISBNList.h"



class WholesaleCost : public BookList {

public:

	WholesaleCost(Book[], int);

	WholesaleCost(const BookList&);



	void sortBooks();

	ISBNList getBooks(std::string);

};
