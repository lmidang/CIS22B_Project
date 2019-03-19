#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Book.h"

/*
template function to calculate the minimum between two parameters of different data types
if the first parameter is greater than the second, return the second
else return the first
*/
template <typename TypeName>
TypeName minimum(TypeName a, TypeName b) {
	return (a > b) ? b : a;
}

/*
template function to calculate the maximum between two parameters of different data types
if the first parameter is smaller than the second, return the second
else return the first
*/
template <typename TypeName>
TypeName maximum(TypeName a, TypeName b) {
	return (a < b) ? b : a;
}

/*
template function to compare two parameters of different data types
if the first parameter is equal to the second
	return 0
if the first parameter is smaller than the second
	return 1
if the first parameter is greater than the second
	return -1
*/
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
	Book* books;		//member variable for an array of books
	int size;		//member variable for the size of the array

public:
	BookList();		//default constructor
	BookList(Book*, int);		//two argument constructor
	BookList(const BookList&);		//one argument constructor
	virtual ~BookList();		//destructor

	//pure virtual function to sort the books in the books array and will be implemented in the derived classes
	virtual void sortBooks() = 0;

	int getSize();		//function to return the size of the array
	Book* getBooks();		//function to return the books array

	int doesBookExist(Book);		//function to check if a Book exists in the books array
	int doesBookExist(unsigned long long); 
	int addBook(Book);				//function to add a book to the books array
	int removeBook(Book);			//function to remove a book from the books array
	void updateBookInfo(Book);		//function to change the information for a Book in the books array

	void saveBookListData(std::string);		//function to print the information for all the books in the array into a file
	virtual void printBooks();		//function to print the information for all the books in the array onto the screen
	double printWholesaleValue();		//function to print the wholesale cost for all the books in the array and calculate the total wholesale cost
	double printRetailValue();		//function to print the retail price for all the books in the array and calculate the total retail price
};