#pragma once

#ifndef ISBNLIST_H
#define ISBNLIST_H

#include <iostream>
#include "BookList.h"

class ISBNList : public BookList {
public:
	//default constructor that simply calls the BookList's constructor
	ISBNList();
	//two argument constructor that takes a Book array and its size and passes it to the BookList's constructor
	ISBNList(Book[], int);
	//copy constructor that takes a constant reference to a BookList object and passes it to the BookList constructor
	ISBNList(const BookList&);

	//function that uses selection sort to sort all the books in the books array by ISBN
	void sortBooks();
	//Function that finds a Book in the books array using binary search
	Book getBook(std::string);
};

#endif