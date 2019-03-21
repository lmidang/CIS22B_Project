#define _CRT_SECURE_NO_WARNINGS

#include "AuthorList.h"

/*
Two argument constructor that takes an array of Book objects and its size as the parameters
It calls the base class's constructor and passes both the parameters to that constructor
*/
AuthorList::AuthorList(Book b[], int s) : BookList(b, s) {

}

/*
Copy constructor that takes a constant reference to a BookList object as the parameter
It calls the base class's constructor and passes the parameter to that constructor
*/
AuthorList::AuthorList(const BookList& bl) : BookList(bl) {

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

void AuthorList::sortBooks() {
	int startIndex;		// starting index
	int minIndex;		// index for the minimum value

	//for loop to go through all the Books except the last one
	for (startIndex = 0; startIndex < size - 1; startIndex++) {
		minIndex = startIndex;	// set minimum value index to starting index
		std::string minAuthor = books[minIndex].getAuthor();	//the current author is the smallest author
		//for loop to go through the Books in the array after the current Book
		for (int index = startIndex + 1; index < size; index++) {
			//if there is an author in the books array that comes before the current author save it.
			if (compare(minAuthor, books[index].getAuthor()) < 0) {
				minAuthor = minimum(minAuthor, books[index].getAuthor());
				minIndex = index;
			}
		}
		//switch the current Book with the Book that has the smallest author.
		Book tempB = books[minIndex];
		books[minIndex] = books[startIndex];
		books[startIndex] = tempB;
	}

}

/*
Function that goes through all the books in the books array and 
creates an ISBNList with all the books that have the name of the author provided by the user.
Takes the name of the author as its parameter and returns an ISBNList with all the books that have the author's name in it.
Go through every book in the array
	compare each book's author with the author name provided by the user
	if a book with that author's name exists in the array, 
		add the book to ISBNlist
	if a book with that author's name doesn't exist 
	and all the books with that author's name have been added to the ISBNList
		break from the for loop
return the ISBNList
*/
ISBNList AuthorList::getBooks(std::string author) {
	int numOfBooksAdded = 0;
	const int numBooks = size;
	ISBNList bl;
	for (int i = 0; i < size; i++) {	//go through every book in the books array
		//compare the current book's author with the author name provided by the user
		if (compare(books[i].getAuthor(), author) == 0) {
			bl.addBook(books[i]);	//if a book with that author's name exists, add the book to an ISBNList
			numOfBooksAdded++;	//increase the number of books added to ISBNList by one
		}
		//if all the books with that author's name have been added to the ISBNList and there are no more books with that author's name
		else if (numOfBooksAdded > 0) {
			break;	//break from the for loop
		}
	}
	return bl;	//return the ISBNList
}