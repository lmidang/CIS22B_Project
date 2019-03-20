#define _CRT_SECURE_NO_WARNINGS

#include "ISBNList.h"

/*
Default constructor that simply calls the base class's constructor
*/
ISBNList::ISBNList() : BookList() {

}

/*
Two argument constructor that takes an array of Book objects and its size as the parameters
It calls the base class's constructor and passes both the parameters to that constructor
*/
ISBNList::ISBNList(Book b[], int s) : BookList(b, s) {
}


/*
Copy constructor that takes a constant reference to a BookList object as the parameter
It calls the base class's constructor and passes the parameter to that constructor
*/
ISBNList::ISBNList(const BookList& bl) : BookList(bl) {
}

/*
Function to sort the books by ISBN
Go through all the Books (except the last one) in the Book list
		Save The current Book's ISBN as the smallest ISBN.
		Save the current index as the smallest index.
		Compare the current Book's ISBN with the remaining Books' ISBNs in the Book list
		If a Book's ISBN smaller than the current Book's ISBN is found:
			Save that Book's ISBN as the smallest ISBN
			Save that index as the smallest index
		Switch the current Book with the Book that has the smallest ISBN.
Continue until all the Books have been compared
*/
void ISBNList::sortBooks() {

	int startIndex;		// starting index
	int minIndex;		// index for the minimum value

	//for loop to go through all the Books except the last one
	for (startIndex = 0; startIndex < (size - 1); startIndex++) {
		minIndex = startIndex;	// set minimum value index to starting index
		std::string minISBN = books[minIndex].getISBN();	//the current ISBN is the smallest ISBN

		//for loop to go through the Books in the array after the current Book
		for (int index = startIndex + 1; index < size; index++) {
			//if there is an ISBN in the books array that comes before the current ISBN save it.
			minISBN = minimum(minISBN, books[index].getISBN());
			minIndex = index;
		}
		//switch the current Book with the Book that has the smallest ISBN.
		Book tempB = books[minIndex];
		books[minIndex] = books[startIndex];
		books[startIndex] = tempB;
	}
}

/*
Function that finds a Book in the books array using binary search
 The first index is zero.
The last index is the last element in the Book list array
position is equal to -1

while position is equal to -1 in the Book list and firstInd < lastInd
	Start in the middle of the array
	Compare the middle Book's ISBN with the ISBN provided by the user
	if middle Book's ISBN == ISBN provided by the user
		position = middle index
	if middle > input
		lastInd is middle index - 1
	if middle < input
		firstInd is middle index + 1
if position is equal to -1
	throw an exception saying that the Book was not found.
Return index of word.
*/


Book ISBNList::getBook(std::string bISBN) {
	int firstElement = 0;		// index of the first element to search through
	int lastElement = size - 1;	// index of the last element to search through + 1
	int middle;					// index of the middle element
	int position = -1;			// position of the Book found  (set to -1 by default)

	// loop while position is still -1 (Book not found) and the first element < last element
	while ((position == -1) && (firstElement <= lastElement)) {
		// set middle to the average of first element and last element (truncate if necessary)
		middle = (firstElement + lastElement) / 2;
		//compare the ISBN passed in as a parameter bISBN with the ISBN stored in the middle Book of the books array
		int comparison = compare(books[middle].getISBN(), bISBN);

		// if bISBN matches the ISBN stored in the middle Book of the books array
		if (comparison == 0) {
			position = middle;	//set the position to middle
		}
		else if (comparison < 0) {
			// if bISBN is less than the that of middle Book, set lastElement to middle
			lastElement = middle - 1;
		}
		else {
			// If bISBN is greater than the middle Book, set firstElement to middle + 1
			firstElement = middle + 1;
		}
	}

	//return the Book at the position in which it was found in the books array
	return books[position];
}