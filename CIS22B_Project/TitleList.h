#pragma once

#ifndef TITLELIST_H
#define TITLELIST_H

#include <iostream>
#include "BookList.h"
#include "ISBNList.h"

class TitleList : public BookList {
public:
	//two argument constructor that takes a Book array and its size and passes it to the BookList's constructor
	TitleList(Book[], int);
	//copy constructor that takes a constant reference to a BookList object and passes it to the BookList constructor
	TitleList(const BookList&);

	//function that uses selection sort to sort all the books in the books array by Title
	void sortBooks();
	//Function that goes through all the books in the books array and
		//creates an ISBNList with all the books that have the title name provided by the user
	ISBNList getBooks(std::string);
};

#endif