#pragma once

#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>


class Book {

private:
	unsigned int mISBN;
	std::string mTitle;
	std::string mAuthor;
	std::string mPublisher;
	std::string mDateAdded;
	int mQuantOnHand;
	double mWholeSale;
	double mRetail;

public:
	Book();
	Book(unsigned int, std::string, std::string, std::string, std::string, int, double, double);
	void setISBN(unsigned int);
	void setTitle(std::string);
	void setAuthor(std::string);
	void setPublish(std::string);
	void setDateAdd(std::string);
	void setQuantity(int);
	void setWholeSale(double);
	void setRetail(double);
	unsigned int getISBN() const;
	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getPublish() const;
	std::string getDateAdd() const;
	int getQuantity() const;
	double getWholeSale() const;
	double getRetail() const;
};

#endif