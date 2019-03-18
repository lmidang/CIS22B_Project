#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <string>

#include "Book.h"


/*
default constructor that initializes the member variables with 0 or " ".
the date member variable is initialized as 0000/00/00 (YYYY-MM-DD)
*/

Book::Book() {

	mISBN = 0;
	mTitle = " ";
	mAuthor = " ";
	mPublisher = " ";
	mDateAdded = "0000/00/00";	// YYYY-MM-DD
	mQuantOnHand = 0;
	mWholeSale = 00.00;
	mRetail = 00.00;
}

/*
eight argument constructor that initializes all the member variables
*/

Book::Book(unsigned long long i, std::string t, std::string a, std::string p, std::string d, int q, double w, double r) {

	mISBN = i;
	mTitle = t;
	mAuthor = a;
	mPublisher = p;
	mDateAdded = d;	//YYYY-MM-DD
	mQuantOnHand = q;
	mWholeSale = w;
	mRetail = r;
}

/*
mutator method for the mISBN member variable
*/
void Book::setISBN(unsigned long long i) {

	mISBN = i;

}

/*
mutator method for the mTitle member variable
*/
void Book::setTitle(std::string t) {

	mTitle = t;

}

/*
mutator method for the mAuthor member variable
*/
void Book::setAuthor(std::string a) {

	mAuthor = a;

}

/*
mutator method for the mPublisher member variable
*/
void Book::setPublish(std::string p) {

	mPublisher = p;

}

/*
mutator method for the mDateAdded member variable
*/
void Book::setDateAdd(std::string da) {

	mDateAdded = da;

}

/*
mutator method for the mQuantOnHand member variable
*/
void Book::setQuantity(int q) {

	mQuantOnHand = q;

}

/*
mutator method for the mWholeSale member variable
*/
void Book::setWholeSale(double ws) {

	mWholeSale = ws;

}
/*
mutator method for the mRetail member variable
*/
void Book::setRetail(double r) {

	mRetail = r;

}

/*
accessor method for the mISBN member variable
*/
unsigned long long Book::getISBN() const {

	return mISBN;

}

/*
accessor method for the mTitle member variable
*/
std::string Book::getTitle() const {

	return mTitle;

}

/*
accessor method for the mAuthor member variable
*/
std::string Book::getAuthor() const {

	return mAuthor;

}

/*
accessor method for the mPublisher member variable
*/
std::string Book::getPublish() const {

	return mPublisher;

}

/*
accessor method for the mDateAdded member variable
*/
std::string Book::getDateAdd() const {

	return mDateAdded;

}

/*
accessor method for the mQuantOnHand member variable
*/
int Book::getQuantity() const {

	return mQuantOnHand;

}

/*
accessor method for the mWholeSale member variable
*/
double Book::getWholeSale() const {

	return mWholeSale;

}

/*
accessor method for the mRetail member variable
*/
double Book::getRetail() const {

	return mRetail;

}