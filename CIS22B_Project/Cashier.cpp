#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include "Book.h"
#include "Cashier.h"
#include "BookList.h"
#include "ISBNList.h"



//default constructor function
Cashier::Cashier()
{
	inputISBN = 0;
}

Cashier::Cashier(ISBNList* Bl)
{
	isbn = Bl;
}

//getter functions
unsigned long long int Cashier::getInputISBN() const
{
	return inputISBN;
}

//Book getCartList()
//{
//	return cartList[i];
//}

//setter functions
void Cashier::setInputISBN(unsigned long long int I)
{
	inputISBN = I;
}

void Cashier::setCartList(Book isbnCartList[50]) //unneccessary?
{
	cartList[50] = isbnCartList[50];
}

void Cashier::ISBNArrayAdd(unsigned long long int ISBN)
{
	static int i = 0;
	cartList[i] = books[ISBNList::getBook(ISBN)]; //attempting to store values of data in a position in books to cartlist
	i++;
}


//missing function to subtract from cart
//missing function to subtract/add a book from inventory list file
//missing function to print isbn, name quantity, and price values from cart


double Cashier::getSalesTax()
{
	double SALES_TAX = .09;
	double salesTax = getSubTotal() * SALES_TAX;
	return salesTax;
}

double Cashier::getSubTotal()
{
	double subTotal = 0;
	//for (unsigned int i = 0; i < size of cart ; i++)
		//subtotal += cartList[i].getRetailPrice() * cartlist[i].getQuantity();
	subTotal = 10.00; //test delete later
	return subTotal;
}