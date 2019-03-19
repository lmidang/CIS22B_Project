#pragma once
#include<iostream>
#include<string>
#include "Book.h"
#include "BookList.h"
#include "ISBNList.h"

class Cashier 
{
protected:
	ISBNList* mpCartList; //member variable for ISBNList objects
	BookList* mpInventory; //member variable for BookList objects
	unsigned long long int mInputISBN; //user input ISBN
public:
	class isbnDoesNotExistException {}; //empty class for exceptions
	class negativeQtyException {}; //empty class for exceptions
	class notEnoughInStockException {}; //empty class for exceptions

	Cashier(BookList*); //constructor
	~Cashier(); //destructor

	//basic getter function for user entered isbn
	unsigned long long int getInputISBN() const;


	//basic setter function for user entered isbn
	void setInputISBN(unsigned long long int);

	//function to put isbn sorted book object into cart array 
	void addToCart(unsigned long long int, int);
	
	//function to subtract from cart
	int removeFromCart(unsigned long long, int);
	
	// function to subtract/add books from inventory list file
	void updateInventory(std::string);
	
	// function to print isbn, name quantity, and price values from cart
	void printCart();
	
	double getSalesTax(); //function to multiply sales tax to price
	double getSubTotal(); //function to multiply add total prices in cart to obtain a subtotal
};
