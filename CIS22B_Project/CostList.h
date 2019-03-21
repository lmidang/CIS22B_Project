#pragma once

#ifndef COSTLIST_H
#define COSTLIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include "BookList.h"
#include "ISBNList.h"

class CostList : public BookList {

public:
	//two argument constructor that takes a Book array and its size and passes it to the BookList's constructor
	CostList(Book[], int);
	//copy constructor that takes a constant reference to a BookList object and passes it to the BookList constructor
	CostList(const BookList&);

	//function that uses selection sort to sort all the books in the books array by Wholesale Cost 
	void sortBooks();
	//function that prints the ISBN, Title, Author, and Wholesale Cost for all the books in the books array
	void printBooks();
};

#endif