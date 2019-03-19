#pragma once
#include<iostream>
#include<string>
#include "Book.h"
#include "BookList.h"
#include "ISBNList.h"

class Cashier 
{
protected:
	ISBNList* mpCartList;
	BookList* mpInventory;
	unsigned long long int mInputISBN;
//	Book cartList[50];
public:
	class isbnDoesNotExistException {};
	class negativeQtyException {};
	class notEnoughInStockException {};

	Cashier(BookList*); 
	~Cashier();

	//getter functions
	unsigned long long int getInputISBN() const;


	//setter functions
	void setInputISBN(unsigned long long int);

	//put isbn sorted book object into cart array 
	void ISBNArrayAdd(unsigned long long int, int);
	
	// function to subtract from cart
	int removeFromCart(unsigned long long, int);
	// function to subtract/add books from inventory list file
	void updateInventory(std::string);
	// function to print isbn, name quantity, and price values from cart
	void printCart();
	
	double getSalesTax();
	double getSubTotal();
};
