#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include "Book.h"
#include "Cashier.h"
#include "BookList.h"
#include "ISBNList.h"

Cashier::Cashier(BookList* bl)
{
	mInputISBN = 0;
	mpCartList = new ISBNList();
	mpInventory = bl;
}

Cashier::~Cashier(){
	if (mpCartList != nullptr) {
		delete mpCartList;
		mpCartList = nullptr;
	}
}

//getter functions
unsigned long long int Cashier::getInputISBN() const
{
	return mInputISBN;
}

//Book getCartList()
//{
//	return cartList[i];
//}

//setter functions
void Cashier::setInputISBN(unsigned long long int I)
{
	if (mpInventory->doesBookExist(I) < 0) {
		throw isbnDoesNotExistException();
	}
	mInputISBN = I;
}

/*
void Cashier::setCartList(Book isbnCartList[50]) //unneccessary?
{
	cartList[50] = isbnCartList[50];
}
*/

void Cashier::ISBNArrayAdd(unsigned long long int ISBN, int qty)
{
	int index = mpInventory->doesBookExist(ISBN);
	int cartQty = qty;
	if (index > -1) {
		Book invB = mpInventory->getBooks()[index];

		int cartIndex = mpCartList->doesBookExist(ISBN);
		if (cartIndex > -1) {
			Book b = mpCartList->getBooks()[cartIndex];
			cartQty += b.getQuantity();
		}

		if (cartQty > invB.getQuantity()) {
			throw notEnoughInStockException();
		}
		else {
			Book b = Book(invB);
			b.setQuantity(qty);
			mpCartList->addBook(b);
		}
	}
	else {
		throw isbnDoesNotExistException();
	}
}

//missing function to subtract from cart
int Cashier::removeFromCart(unsigned long long isbn, int qty) {
	int index = mpCartList->doesBookExist(isbn);
	if (index > -1) {
		Book b = mpCartList->getBooks()[index];
		int bQty = subtractBookQty(b, qty);
		if (bQty > 0) {
			b.setQuantity(bQty);
			mpCartList->updateBookInfo(b);
		}
		else if (bQty == 0) {
			mpCartList->removeBook(b);
		}
		else {
			throw negativeQtyException();
		}
	}
	else {
		throw isbnDoesNotExistException();
	}
	return mpCartList->getSize();
}

// function to subtract books from inventory list file
void Cashier::updateInventory(std::string fileName) {
	int size = mpCartList->getSize();
	for (int i = 0; i < size; i++) {
		Book bookCart = mpCartList->getBooks()[i];
		Book bookInv = mpInventory->getBooks()[mpInventory->doesBookExist(bookCart.getISBN())];

		int qty = subtractBookQty(bookInv, bookCart);

		bookInv.setQuantity(qty);
		mpInventory->updateBookInfo(bookInv);
	}
	mpInventory->saveBookListData(fileName);
}

// function to print isbn, name quantity, and price values from cart
void Cashier::printCart() {
	int size = mpCartList->getSize();
	mpCartList->sortBooks();
	for (int i = 0; i < size; i++) {
		Book b = mpCartList->getBooks()[i];
		std::cout << std::setw(20) << b.getQuantity() << std::setw(20) << b.getISBN() << std::setw(40) << b.getTitle();
		std::cout << std::setw(20) << b.getRetail() << std::setw(20) << b.getQuantity() * b.getRetail() << std::endl;
	}
}

double Cashier::getSalesTax()
{
	double SALES_TAX = .09;
	double salesTax = getSubTotal() * SALES_TAX;
	return salesTax;
}

double Cashier::getSubTotal()
{
	int size = mpCartList->getSize();

	double subTotal = 0;
	for (int i = 0; i < size; i++) {
		Book b = mpCartList->getBooks()[i];
		subTotal += (b.getQuantity() * b.getRetail());
	}
	//subTotal = 10.00; //test delete later
	return subTotal;
}