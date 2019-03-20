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
	std::string mInputISBN; //user input ISBN
public:
	class isbnDoesNotExistException {}; //empty class for exceptions
	class negativeQtyException {}; //empty class for exceptions
	class notEnoughInStockException {}; //empty class for exceptions

	Cashier(BookList*); //constructor
	~Cashier(); //destructor

	//basic getter function for user entered isbn
	std::string getInputISBN() const;


	//basic setter function for user entered isbn
	void setInputISBN(std::string);

	//function to put isbn sorted book object into cart array 
	void addToCart(std::string, int);
	
	//function to subtract from cart
	int removeFromCart(std::string, int);
	
	// function to subtract/add books from inventory list file
	void updateInventory(std::string);
	
	// function to print isbn, name quantity, and price values from cart
	void printCart();
	
	double getSalesTax(); //function to multiply sales tax to price
	double getSubTotal(); //function to multiply add total prices in cart to obtain a subtotal
};
