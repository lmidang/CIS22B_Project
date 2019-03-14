#include <iostream>
#include <string>
#include "Book.h"

Book::Book() {
	mISBN = 0;
	mTitle = " ";
	mAuthor = " ";
	mPublisher = " ";
	mDateAdded = "0000/00/00";	// YYYY/MM/DD
	mQuantOnHand = 0;
	mWholeSale = 00.00;
	mRetail = 00.00;
}

Book::Book(unsigned int i, std::string t, std::string a, std::string p, std::string d, int q, double w, double r) {
	mISBN = i;
	mTitle = t;
	mAuthor = a;
	mPublisher = p;
	mDateAdded = d;
	mQuantOnHand = q;
	mWholeSale = w;
	mRetail = r;
}

void Book::setISBN(unsigned int i) {
	mISBN = i;
}

void Book::setTitle(std::string t) {
	mTitle = t;
}

void Book::setAuthor(std::string a) {
	mAuthor = a;
}

void Book::setPublish(std::string p) {
	mPublisher = p;
}

void Book::setDateAdd(std::string da) {
	mDateAdded = da;
}

void Book::setQuantity(int q) {
	mQuantOnHand = q;
}

void Book::setWholeSale(double ws) {
	mWholeSale = ws;
}

void Book::setRetail(double r) {
	mRetail = r;
}

unsigned int Book::getISBN() const {
	return mISBN;
}

std::string Book::getTitle() const {
	return mTitle;
}

std::string Book::getAuthor() const {
	return mAuthor;
}

std::string Book::getPublish() const {
	return mPublisher;
}

std::string Book::getDateAdd() const {
	return mDateAdded;
}

int Book::getQuantity() const {
	return mQuantOnHand;
}

double Book::getWholeSale() const {
	return mWholeSale;
}

double Book::getRetail() const {
	return mRetail;
}