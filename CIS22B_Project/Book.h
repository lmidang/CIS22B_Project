#pragma once

#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

class Book {

private:

	unsigned long long mISBN;	//member variables
	std::string mTitle;
	std::string mAuthor;
	std::string mPublisher;
	std::string mDateAdded;
	int mQuantOnHand;
	double mWholeSale;
	double mRetail;

public:

	Book();	//default constructor
	Book(unsigned long long, std::string, std::string, std::string, std::string, int, double, double);	//8 argument constructor
	//mutator methods
	void setISBN(unsigned long long);
	void setTitle(std::string);
	void setAuthor(std::string);
	void setPublish(std::string);
	void setDateAdd(std::string);
	void setQuantity(int);
	void setWholeSale(double);
	void setRetail(double);
	//accessor methods
	unsigned long long getISBN() const;
	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getPublish() const;
	std::string getDateAdd() const;
	int getQuantity() const;
	double getWholeSale() const;
	double getRetail() const;
};
#endif