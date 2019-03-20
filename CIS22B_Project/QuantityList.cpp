#define _CRT_SECURE_NO_WARNINGS

#include "QuantityList.h"

/*
Two argument constructor that takes an array of Book objects and its size as the parameters
It calls the base class's constructor and passes both the parameters to that constructor
*/
QuantityList::QuantityList(Book b[], int s) : BookList(b, s) {
}


/*
Copy constructor that takes a constant reference to a BookList object as the parameter
It calls the base class's constructor and passes the parameter to that constructor
*/
QuantityList::QuantityList(const BookList& bl) : BookList(bl) {
}

/*
Function to sort the books by Quantity
Go through all the Books (except the last one) in the Book list
		Save The current Book's Quantity as the largest Quantity.
		Save the current index as the largest index.
		Compare the current Book's Quantity with the remaining Books' Quantitys in the Book list
		If a Book's Quantity larger than the current Book's Quantity is found:
			Save that Book's Quantity as the largest Quantity
			Save that index as the max index
		Switch the current Book with the Book that has the largest Quantity.
Continue until all the Books have been compared
*/
void QuantityList::sortBooks() {

	int startIndex;		// starting index
	int maxIndex;		// index for the max value

	//for loop to go through all the Books except the last one
	for (startIndex = 0; startIndex < (size - 1); startIndex++) {
		maxIndex = startIndex;	// set max value index to starting index
		int maxQty = books[maxIndex].getQuantity();	//the currentQuantity is the largest Quantity

		//for loop to go through the Books in the array after the current Book
		for (int index = startIndex + 1; index < size; index++) {
			//if there is an Quantity in the books array that comes before the current Quantity save it.
			if (compare(maxQty, books[index].getQuantity()) > 0) {
				maxQty = maximum(maxQty, books[index].getQuantity());
				maxIndex = index;
			}
		}
		//switch the current Book with the Book that has the largest Quantity.
		Book tempB = books[maxIndex];
		books[maxIndex] = books[startIndex];
		books[startIndex] = tempB;
	}
}

/*
Function to print the ISBN, Title, Author, and the Quantity for all the books
*/
void QuantityList::printBooks() {
	std::cout << "ISBN" << std::setw(10) << "Title" << std::setw(10) << "Author" << std::setw(10) << "Quantity" << std::endl;
	//prints the header before printing all the books
	for (int i = 0; i < size; i++) {
		Book b = books[i];//get every Book from the books array 
		//print the ISBN, Title, Author, and Quantity for each Book
		std::cout << b.getISBN() << "," << b.getTitle() << "," << b.getAuthor() << "," << " $" << b.getQuantity() << std::endl;
	}
}