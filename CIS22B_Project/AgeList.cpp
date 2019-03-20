#define _CRT_SECURE_NO_WARNINGS
#include "AgeList.h"

/*
Two argument constructor that takes an array of Book objects and its size as the parameters
It calls the base class's constructor and passes both the parameters to that constructor
*/
AgeList::AgeList(Book b[], int s) : BookList(b, s) {	
}

/*
Copy constructor that takes a constant reference to a BookList object as the parameter
It calls the base class's constructor and passes the parameter to that constructor
*/
AgeList::AgeList(const BookList& bl) : BookList(bl) {

}

/*
Function to sort the books by Age
Go through all the Books (except the last one) in the Book list
		Save The current Book's age as the smallest age.
		Save the current index as the smallest index.
		Compare the current Book's age with the remaining Books' ages in the Book list
		If a Book's age smaller than the current Book's age is found:
			Save that Book's age as the smallest age
			Save that index as the smallest index
		Switch the current Book with the Book that has the smallest age.
Continue until all the Books have been compared
*/

void AgeList::sortBooks() {
	int startIndex;		// starting index
	int minIndex;		// index for the minimum value
	//for loop to go through all the Books except the last one
	for (startIndex = 0; startIndex < (size - 1); startIndex++) {
		minIndex = startIndex;	// set minimum value index to starting index
		std::string minAge = books[minIndex].getDateAdd();	 //the current age is the smallest age
		//for loop to go through the Books in the array after the current Book
		for (int index = startIndex + 1; index < getSize(); index++) {
			//if there is an age in the books array that comes before the current age save it.
			if (compare(minAge, books[index].getDateAdd()) < 0) {
				minAge = minimum(minAge, books[index].getDateAdd());
				minIndex = index;
			}
		}
		//switch the current Book with the Book that has the smallest age.
		Book tempB = books[minIndex];
		books[minIndex] = books[startIndex];
		books[startIndex] = tempB;
	}
}

/*
Function to print the ISBN, Title, Author, and the Age for all the books
*/

void AgeList::printBooks() {
	std::cout << "ISBN" << std::setw(10) << "Title" << std::setw(10) << "Author" << std::setw(10) << "Date Added" << std::endl;
	//prints the header before printing all the books
	for (int i = 0; i < size; i++) {
		Book b = books[i];	//get every Book from the books array 
		//print the ISBN, Title, Author, and Age for each Book
		std::cout << b.getISBN() << "," << b.getTitle() << "," << b.getAuthor() << "," << b.getDateAdd() << std::endl;
	}
}