#define _CRT_SECURE_NO_WARNINGS

#include "CostList.h"

/*
Two argument constructor that takes an array of Book objects and its size as the parameters
It calls the base class's constructor and passes both the parameters to that constructor
*/
CostList::CostList(Book b[], int s) : BookList(b, s) {
}


/*
Copy constructor that takes a constant reference to a BookList object as the parameter
It calls the base class's constructor and passes the parameter to that constructor
*/
CostList::CostList(const BookList& bl) : BookList(bl) {
}

/*
Function to sort the books by Wholesale Cost
Go through all the Books (except the last one) in the Book list
		Save The current Book's wholesale cost as the smallest wholesale cost.
		Save the current index as the smallest index.
		Compare the current Book's wholesale cost with the remaining Books' wholesale costs in the Book list
		If a Book's wholesale cost smaller than the current Book's wholesale cost is found:
			Save that Book's wholesale cost as the smallest wholesale cost
			Save that index as the smallest index
		Switch the current Book with the Book that has the smallest wholesale cost.
Continue until all the Books have been compared
*/
void CostList::sortBooks() {

	int startIndex;		// starting index
	int minIndex;		// index for the minimum value

	//for loop to go through all the Books except the last one
	for (startIndex = 0; startIndex < (size - 1); startIndex++) {
		minIndex = startIndex;	// set minimum value index to starting index
		double minWholeSale = books[minIndex].getWholeSale();	//the current wholesale cost is the smallest wholesale cost

		//for loop to go through the Books in the array after the current Book
		for (int index = startIndex + 1; index < size; index++) {
			//if there is an wholesale cost in the books array that comes before the current wholesale cost save it.
			minWholeSale = minimum(minWholeSale, books[index].getWholeSale());
			minIndex = index;
		}
		//switch the current Book with the Book that has the smallest wholesale cost.
		Book tempB = books[minIndex];
		books[minIndex] = books[startIndex];
		books[startIndex] = tempB;
	}
}

/*
Function to print the ISBN, Title, Author, and the Wholesale Cost for all the books
*/
void CostList::printBooks() {
	std::cout << "ISBN" << std::setw(10) << "Title" << std::setw(10) << "Author" << std::setw(10) << "Wholesale Cost" << std::endl;
	//prints the header before printing all the books
	for (int i = 0; i < size; i++) {
		Book b = books[i];//get every Book from the books array 
		//print the ISBN, Title, Author, and Wholesale Cost for each Book
		std::cout << b.getISBN() << "," << b.getTitle() << "," << b.getAuthor() << "," << " $" << b.getWholeSale() << std::endl;
	}
}