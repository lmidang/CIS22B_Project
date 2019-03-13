#include "AuthorList.h"

AuthorList::AuthorList(Book b[], int s) : BookList(b, s) {

}

AuthorList::AuthorList(const BookList& bl) : BookList(bl) {

}

void AuthorList::sortBooks() {
	int startIndex;		// starting index
	int minIndex;		// index for the minimum value

	// loop through the array from 0
	for (startIndex = 0; startIndex < size; startIndex++) {
		minIndex = startIndex;	// set minimum value index to starting index
		std::string minAuthor = books[minIndex].getAuthor();	// set to the element at minIndex

		// loop through the array from one after the startIndex
		for (int index = startIndex + 1; index < size; index++) {
			// if the word at the index is lower than minValue set minIndex to index and minValue to word
			minAuthor = minimum(minAuthor, books[index].getAuthor());
		}

		// switch the element at minIndex and the element at startIndex
		Book tempB = books[minIndex];
		books[minIndex] = books[startIndex];
		books[startIndex] = tempB;
	}
}

// under assumption that books have been sorted
ISBNList AuthorList::getBooks(std::string author) {
	int num = 0;
	const int numBooks = size;
	ISBNList bl;

	for (int i = 0; i < size; i++) {
		if (compare(books[i].getAuthor(), author) == 0) {
			bl.addBook(books[i]);
		}
		else if (num > 0) {
			break;
		}
	}

	return bl;
}