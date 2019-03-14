#pragma once

#include <iostream>

#include "BookList.h"

#include "ISBNList.h"



class QuantityList : public BookList {

public:

	QuantityList(Book[], int);

	QuantityList(const BookList&);



	void sortBooks();

};
