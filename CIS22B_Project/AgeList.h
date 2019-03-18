#pragma once

#include <iostream>
#include <iomanip>
#include <string>

#include "BookList.h"

class AgeList : public BookList {

public:

	//two argument constructor that takes a Book array and its size and passes it to the BookList's constructor
	AgeList(Book[], int);

	//copy constructor that takes a constant reference to a BookList object and passes it to the BookList constructor
	AgeList(const BookList&);

	//function that uses selection sort to sort all the books in the books array by Age 
	void sortBooks();

	//function that prints the ISBN, Title, Author, and Age for all the books in the books array
	void printBooks();

};
