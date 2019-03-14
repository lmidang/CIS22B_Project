#pragma once
#include <iostream>
#include <string>
#include "BookList.h"


class PriceList : public BookList {

public:

	PriceList(Book[], int);

	PriceList(const BookList&);



	void sortBooks();
};
