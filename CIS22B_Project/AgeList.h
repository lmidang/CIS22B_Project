#pragma once

#include <iostream>
#include <string>

#include "BookList.h"



class AgeList : public BookList {

public:

	AgeList(Book[], int);

	AgeList(const BookList&);

	void sortBooks();
	void printBooks();
};
