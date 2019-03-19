#define _CRT_SECURE_NO_WARNINGS

#include "TitleList.h"

/*
Two argument constructor that takes an array of Book objects and its size as the parameters
It calls the base class's constructor and passes both the parameters to that constructor
*/
TitleList::TitleList(Book b[], int s) : BookList(b, s) {
}


/*
Copy constructor that takes a constant reference to a BookList object as the parameter
It calls the base class's constructor and passes the parameter to that constructor
*/
TitleList::TitleList(const BookList& bl) : BookList(bl) {
}

/*
Function to sort the books by Title
Go through all the Books (except the last one) in the Book list
		Save The current Book's Title as the smallest Title.
		Save the current index as the smallest index.
		Compare the current Book's Title with the remaining Books' Titles in the Book list
		If a Book's Title smaller than the current Book's Title is found:
			Save that Book's Title as the smallest Title
			Save that index as the smallest index
		Switch the current Book with the Book that has the smallest Title.
Continue until all the Books have been compared
*/
void TitleList::sortBooks() {

	int startIndex;		// starting index
	int minIndex;		// index for the minimum value

	//for loop to go through all the Books except the last one
	for (startIndex = 0; startIndex < (size - 1); startIndex++) {
		minIndex = startIndex;	// set minimum value index to starting index
		std::string minTitle = books[minIndex].getTitle();	//the current Title is the smallest Title

		//for loop to go through the Books in the array after the current Book
		for (int index = startIndex + 1; index < size; index++) {
			//if there is an Title in the books array that comes before the current Title save it.
			minTitle = minimum(minTitle, books[index].getTitle());
			minIndex = index;
		}
		//switch the current Book with the Book that has the smallest Title.
		Book tempB = books[minIndex];
		books[minIndex] = books[startIndex];
		books[startIndex] = tempB;
	}
}

/*
Function that goes through all the books in the books array and
creates an ISBNList with all the books that have the title name provided by the user.
Takes the name of the Book as its parameter and returns an ISBNList with all the books that have the title name in it.
Go through every book in the array
	compare each book's title with the title name provided by the user
	if a book with that title name exists in the array,
		add the book to ISBNlist
	if a book with that title name doesn't exist
	and all the books with that title name have been added to the ISBNList
		break from the for loop
return the ISBNList
*/

ISBNList TitleList::getBooks(std::string title) {
	int numOfBooksAdded = 0;
	const int numBooks = size;
	ISBNList bl;
	for (int i = 0; i < size; i++) {	//go through every book in the books array
		//compare the current book's title with the title name provided by the user
		if (compare(books[i].getTitle(), title) == 0) {
			bl.addBook(books[i]);	//if a book with that title name exists, add the book to an ISBNList
			numOfBooksAdded++;	//increase the number of books added to ISBNList by one
		}
		//if all the books with that title name have been added to the ISBNList and there are no more books with that title name
		else if (numOfBooksAdded > 0) {
			break;	//break from the for loop
		}
	}
	return bl;	//return the ISBNList
}