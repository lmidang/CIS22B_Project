#pragma once
#include <iostream>
#include <string>
#include "BookList.h"
#include "ISBNList.h"
#include "AgeList.h"
#include "QuantityList.h"
#include "PriceList.h"

class Report {
protected:
	BookList* booksOriginal;
	BookList* printBooks;
public:
	Report(BookList*);
	~Report();
	void printReport(int);
};