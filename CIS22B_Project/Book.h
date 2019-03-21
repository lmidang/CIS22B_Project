#pragma once

#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

class Book {

protected:
	std::string mISBN;	//member variables
	std::string mTitle;
	std::string mAuthor;
	std::string mPublisher;
	std::string mDateAdded;
	int mQuantOnHand;
	double mWholeSale;
	double mRetail;

public:

	Book();	//default constructor
	Book(std::string, std::string, std::string, std::string, std::string, int, double, double);	//8 argument constructor
	//mutator methods
	void setISBN(std::string);
	void setTitle(std::string);
	void setAuthor(std::string);
	void setPublish(std::string);
	void setDateAdd(std::string);
	void setQuantity(int);
	void setWholeSale(double);
	void setRetail(double);
	//accessor methods
	std::string getISBN() const;
	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getPublish() const;
	std::string getDateAdd() const;
	int getQuantity() const;
	double getWholeSale() const;
	double getRetail() const;

	// friend methods to increase and decrease quantity of a book
	/**
		A friend function that accesses attributes of the Book class
		Takes two Book objects as its parameters and returns the sum of the books’ quantitys.	
		Add the quantity of Book a with the quantity of Book b and returns it.
	*/
	friend int addBookQty(Book a, Book b) {
		return a.mQuantOnHand + b.mQuantOnHand;
	}

	/**
		A friend function that accesses attributes of the Book class
		Takes two Book objects as its parameters and returns the difference of the books’ quantitys.
		Add the quantity of Book a with the quantity of Book b and returns it.
	*/
	friend int subtractBookQty(Book a, Book b) {
		return a.mQuantOnHand - b.mQuantOnHand;
	}

	/**
		A friend function that accesses attributes of the Book class
		Takes a Book object and integer as its parameters and returns the difference of the book's quantity and the integer.
		Add the quantity of Book a with the quantity of Book b and returns it.
	*/
	friend int subtractBookQty(Book a, int b) {
		return a.mQuantOnHand - b;
	}

	// operator overload to print full book information
	/**
		A function that overloads the << operator so that all the attributes of the Book object can be printed in one statement. 
		Takes the output stream and one constant reference to a Book object as its parameters. 
		Prints all the attributes of one Book object to the output stream
	*/
	friend std::ostream& operator<< (std::ostream &out, const Book &b) {
		out << "ISBN: " << b.mISBN << std::endl
			<< "Book Title: " << b.mTitle << std::endl
			<< "Author: " << b.mAuthor << std::endl
			<< "Publisher: " << b.mPublisher << std::endl
			<< "Date Added: " << b.mDateAdded << std::endl
			<< "Quantity-On-Hand: " << b.mQuantOnHand << std::endl
			<< "Wholesale Cost: " << b.mWholeSale << std::endl
			<< "Retail Price: " << b.mRetail << std::endl;
		return out;
	}
};
#endif