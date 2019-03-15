#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "BookList.h"
#include "ISBNList.h"

class CostList : public BookList {

public:
	CostList (Book[], int);
	CostList(const BookList&);

	void sortBooks();
	void printBooks();
};
