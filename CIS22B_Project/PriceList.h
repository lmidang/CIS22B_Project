#pragma once

#include <iostream>

#include "BookList.h"

#include "ISBNList.h"



class PriceList : public BookList {

public:

	PriceList(Book[], int);

	PriceList(const BookList&);



	void sortBooks();
};
