#pragma once

#ifndef REPORT_H
#define REPORT_H

#include <iostream>
#include <string>
#include "BookList.h"
#include "ISBNList.h"
#include "AgeList.h"
#include "QuantityList.h"
#include "CostList.h"

class Report {
protected:
	BookList* booksOriginal;//member variables for BookList objects
	BookList* printBooks;
public:
	Report(BookList*);//one argument constructor
	~Report();//destructor
	void printReport(int);//function to print various reports based on user's choice
};

#endif