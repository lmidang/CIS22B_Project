#pragma once

#ifndef AUTHORLIST_H
#define AUTHORLIST_H

#include <iostream>
#include "BookList.h"
#include "ISBNList.h"

class AuthorList : public BookList {

public:

	//two argument constructor that takes a Book array and its size and passes it to the BookList's constructor
	AuthorList(Book[], int);

	//copy constructor that takes a constant reference to a BookList object and passes it to the BookList constructor
	AuthorList(const BookList&);

	//function that uses selection sort to sort all the books in the books array by Author 
	void sortBooks();

	//function that returns an ISBNList with all books that have the author's name provided by the user
	ISBNList getBooks(std::string);

};

#endif