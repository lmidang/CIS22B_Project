#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Book.h"

template <typename TypeName> 
TypeName minimum(TypeName a, TypeName b) {
	return (a > b) ? b : a;
}

template <typename TypeName>
TypeName maximum(TypeName a, TypeName b) {
	return (a < b) ? b : a;
}

template <typename TypeName>
int compare(TypeName a, TypeName b) {
	if (a == b) {
		return 0;
	}
	else if (a < b) {
		return 1;
	}
	else {
		return -1;
	}
}

class BookList {
protected:
	Book* books;
	int size;

public:
	BookList();
	BookList(Book*, int);
	BookList(const BookList&);
	virtual ~BookList();

	virtual void sortBooks() = 0;

	int getSize();
	Book* getBooks();

	int doesBookExist(Book);
	int addBook(Book);				// adds book to list or increases qty, returns size of list
	int removeBook(Book);			// removes book from the list
	void updateBookInfo(Book);

	void saveBookListData(std::string);
	// prints out the list of books accordingly
	virtual void printBooks();
	double printWholesaleValue();
	double printRetailValue();
};