#pragma once
#include "BookList.h"
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