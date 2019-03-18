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
		Save The current Book's Quantity as the smallest Quantity.
		Save the current index as the smallest index.
		Compare the current Book's Quantity with the remaining Books' Quantitys in the Book list
		If a Book's Quantity smaller than the current Book's Quantity is found:
			Save that Book's Quantity as the smallest Quantity
			Save that index as the smallest index
		Switch the current Book with the Book that has the smallest Quantity.
Continue until all the Books have been compared
*/
void QuantityList::sortBooks() {

	int startIndex;		// starting index
	int minIndex;		// index for the minimum value

	//for loop to go through all the Books except the last one
	for (startIndex = 0; startIndex < (size - 1); startIndex++) {
		minIndex = startIndex;	// set minimum value index to starting index
		int minQty = books[minIndex].getQuantity();	//the currentQuantity is the smallest Quantity

		//for loop to go through the Books in the array after the current Book
		for (int index = startIndex + 1; index < size; index++) {
			//if there is an Quantity in the books array that comes before the current Quantity save it.
			minQty = minimum(minQty, books[index].getQuantity());
			minIndex = index;
		}
		//switch the current Book with the Book that has the smallest Quantity.
		Book tempB = books[minIndex];
		books[minIndex] = books[startIndex];
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