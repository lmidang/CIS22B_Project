#pragma once
#include<iostream>
#include<string>
#include "Book.h"
#include "BookList.h"
#include "ISBNList.h"

class Cashier : public ISBNList
{
protected:
	ISBNList* isbn;
	unsigned long long int inputISBN;
	Book cartList[50];
public:
	Cashier(); //default constructor
	Cashier(ISBNList*); 

	//getter functions
	unsigned long long int getInputISBN() const;


	//setter functions
	void setInputISBN(unsigned long long int);
	void setCartList(Book isbnCartList[50]); //possibly uneccessary



	//put isbn sorted book object into cart array 
	void ISBNArrayAdd(unsigned long long int);
	
	//missing function to subtract from cart
	//missing function to subtract/add a book from inventory list file
	//missing function to print isbn, name quantity, and price values from cart
	

	double getSalesTax();
	double getSubTotal();
};
