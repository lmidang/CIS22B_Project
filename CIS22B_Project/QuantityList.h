#pragma once

#include <iostream>
#include <string>
#include "BookList.h"


class QuantityList : public BookList {

public:

	QuantityList(Book[], int);

	QuantityList(const BookList&);



	void sortBooks();

};
