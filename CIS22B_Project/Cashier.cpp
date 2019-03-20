#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include "Book.h"
#include "Cashier.h"
#include "BookList.h"
#include "ISBNList.h"

Cashier::Cashier(BookList* bl) //constructor with 
{
	mInputISBN = "0000000"; //sets isbn value to deafult of zero
	mpCartList = new ISBNList(); //new dynamically allocated class created from ISBNList
	mpInventory = bl; //copies the address of a pointer to a ISBNList class
}

Cashier::~Cashier(){
	if (mpCartList != nullptr) //if mpCartList exists
	{
		delete mpCartList; //clears mpCartList
		mpCartList = nullptr; //sets the adress to CartList to zero
	}
}

//getter function
std::string Cashier::getInputISBN() const
{
	return mInputISBN;
}


//setter function with exception
void Cashier::setInputISBN(std::string I)
{
	if (mpInventory->doesBookExist(I) < 0)
	{
		throw isbnDoesNotExistException(); //exception if isbn does not exist in inventory file
	}
	mInputISBN = I;
}

//function to add book objects to a cart
void Cashier::addToCart(std::string ISBN, int qty)
{
	int index = mpInventory->doesBookExist(ISBN); //variable index gets position of book 
	int cartQty = qty;
	if (index > -1)
	{
		Book invB = mpInventory->getBooks()[index]; //class Book invB gets book with input isbn

		int cartIndex = mpCartList->doesBookExist(ISBN); //cartIndex gets position of book that was input with an isbn
		if (cartIndex > -1)
		{
			Book b = mpCartList->getBooks()[cartIndex]; //class Book b gets book from index position in cart
			cartQty += b.getQuantity(); //add quantity to book object in cart
		}

		if (cartQty > invB.getQuantity())
		{
			throw notEnoughInStockException(); //exception if quantity of book equals zero
		}
		else
		{
			Book b = Book(invB);
			b.setQuantity(qty); //book class quantity gets quantity of cart
			mpCartList->addBook(b); //adds book into cart by creating a new space in the array
		}
	}
	else
	{
		throw isbnDoesNotExistException(); //exception if isbn doesn not exist
	}
}

//function to subtract book objects from the cart
int Cashier::removeFromCart(std::string isbn, int qty)
{
	int index = mpCartList->doesBookExist(isbn); //variable index gets position of book 
	if (index > -1)
	{
		Book b = mpCartList->getBooks()[index]; //class Book invB gets book with input isbn
		int bQty = subtractBookQty(b, qty);
		if (bQty > 0)
		{
			b.setQuantity(bQty); //set quantity of book in book class
			mpCartList->updateBookInfo(b); //update cartlist by getting quantity of book b
		}
		else if (bQty == 0)
		{
			mpCartList->removeBook(b); //removes book from cart
		}
		else
		{
			throw negativeQtyException(); //exception if isbn is a negative number
		}
	}
	else
	{
		throw isbnDoesNotExistException(); //exception if isbn doesn not exist
	}
	return mpCartList->getSize(); //return size of cartlist in terms of book objects
}

// function to subtract books from inventory list file
void Cashier::updateInventory(std::string fileName)
{
	int size = mpCartList->getSize();
	for (int i = 0; i < size; i++)
	{
		Book bookCart = mpCartList->getBooks()[i]; //class book bookCart gets book in cart
		Book bookInv = mpInventory->getBooks()[mpInventory->doesBookExist(bookCart.getISBN())];

		int qty = subtractBookQty(bookInv, bookCart); //set variable qty to function that removes a book quantity

		bookInv.setQuantity(qty); //set new quantity in Book class
		mpInventory->updateBookInfo(bookInv); //call funstion to update book info of book class object
	}
	mpInventory->saveBookListData(fileName); //saves data directly into file from book class object
}

// function to print quantity, isbn, name, and price values from cart
void Cashier::printCart()
{
	int size = mpCartList->getSize();
	mpCartList->sortBooks();
	for (int i = 0; i < size; i++)
	{
		Book b = mpCartList->getBooks()[i]; //Book b = book in cartlist
		std::cout << std::setw(20) << b.getQuantity() << std::setw(20) << b.getISBN() << std::setw(40) << b.getTitle();
		std::cout << std::setw(20) << b.getRetail() << std::setw(20) << b.getQuantity() * b.getRetail() << std::endl;
	}
}

//function to multipy subtotal function by a tax rate to obtain a taxed value
double Cashier::getSalesTax()
{
	double SALES_TAX = .09; // set sales tax rate to 9%
	double salesTax = getSubTotal() * SALES_TAX; //multiply subtotal by 9%
	return salesTax; //return tax based on subtotal
}


//function to add price values of books multiplied by quantity in cart to obtain a subtotal
double Cashier::getSubTotal()
{
	int size = mpCartList->getSize();

	double subTotal = 0;
	for (int i = 0; i < size; i++) //loops while objects exist in cart
	{
		Book b = mpCartList->getBooks()[i]; //Book b = book in cartlist
		subTotal += (b.getQuantity() * b.getRetail()); //subtotal = quantity times retail value
	}
	return subTotal;
}